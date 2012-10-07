/**
 * @file u_lstream.h
 *
 * Defines an interface for opening character streams.
 * It contains functions and typedefs geared towards the
 * implementation of objects that can convert and read character
 * streams in one encoding to another, and make tests on their
 * character types.
 * All this functionality is done so that the task of supporting
 * various input encodings can be detached from the parser.
 */

#ifndef U_LSTREAM_H_
#define U_LSTREAM_H_

#include "u_defs.h"


/*##############################################################################
 *# ENUMERATIONS ###############################################################
 *############################################################################*/


/** 
 * Represents an action to be executed on a stream.
 */
typedef enum umL_EStreamAction {

	/** Format: @code read(void** out, long* sz, long ctypes) @endcode
	 * 
	 * Reads @c sz characters from the stream, with the specified
	 * @c ctype character types. Returns on @c out a pointer to the
	 * beginning of a buffer containing at most @c sz characters, and
	 * at the end of the read process, sets @c sz to the number of
	 * bytes in the buffer returned.
	 * If the size passed is equal to 0, the stream will try to read
	 * as much data as it can, be it in predefined steps or until
	 * there's available memory to do so.
	 * If the size passed is less than 0, the stream will try to read
	 * all of the data available at once, and will fail if there's no
	 * memory available for the operation.
	 * If @c umL_ISNONE(ctypes) is true, no test is done on the reads.
	 * Note that the buffer is @c const, and is only valid until another
	 * operation is performed on the stream. The stream reader may
	 * (and probably will) deallocate or reutilize the buffer on the next
	 * operation, so be careful.
	 */
	umL_ACT_READ,

	/** Format: @code isctype(int* out, long ctypes) @endcode
	 *
	 * Check to see if the next character on the stream is of the 
	 * @c ctype character types passed. Returns on @c out @c 1 on 
	 * success on identifying all the character types on the 
	 * next character, and @c 0 otherwise. 
	 */
	umL_ACT_ISCTYPE,

	/** Format: @code ctypes(long* out) @endcode
	 * 
	 * Identifies all the character types on the next character on the
	 * stream, and puts it on the location pointed to by @c out.
	 * Does nothing if @c out is @c NULL.
	 */
	umL_ACT_CTYPES,

#if 0
	/* This one will be complicated to implement, and probably, is not
	 * worth the time. Outside code will obtain the stream data on
	 * the encoding it needs, so there's no need to complicate
	 * implementations with a feature that could easily be done by the
	 * caller. */
	/* umL_ACT_CMP,      /* int* out, void** in, long* sz */
#endif

	/** Format: @code discard(long sz, long ctypes) @endcode
	 * Discards the next @c sz characters with the character types
	 * passed as @c ctypes. 
	 * If @c umL_ISNONE(ctypes) is true, no test is done on the reads.
	 * If @c sz  passed is less than or equal to 0, the stream 
	 * effectively discards all of its data, up till it finds end-of-stream.
	 * If @c sz is not @c NULL, the stream returns through it the number of
	 * bytes skipped from the stream.
	 */
	umL_ACT_DISCARD,

	/** Format: @code enc(char** in, char** out) @endcode
	 * Returns the input and output encodings for this stream.
	 * The strings returned are @c const and pure ASCII, @c NULL terminated
	 * strings. They're valid data only until the stream is opened,
	 * because the stream is free to deallocate them when it's closed,
	 * so be careful.
	 */
	umL_ACT_ENC

	/** Format: @code close() @endcode
	 * Closes the stream, freeing any resources used by it. It also
	 * invalidates the stream itself, so that a call to execute any further
	 * action will result in the return of @a umL_ERROR status code.
	 */
	umL_ACT_CLOSE

} umL_EStreamAction;

/**
 * Represents the action to be taken for a stream opener.
 */
typedef enum umL_EStreamOpenerAction {

	/** Format:
	 * @code 
	 *   openfile(umL_FStream* sb, void** sd, char* fname,
	 *            char* outenc, char* inenc)
	 * @endcode
	 * Opens a file @c fname, in the encoding @c inenc, and converts its
	 * contents to the encoding @c outenc. If @c inenc is @c NULL, the
	 * stream opener tries to guess the content's encoding, and opens the
	 * file if it can. In the case of @c openfile, the stream opener may
	 * try to open the file more than once.
	 * The opened stream and its data is returned in @c sb and @c sd,
	 * respectively.
	 */
	umL_ACT_OPENFILE,

	/** Format:
	 * @code
	 *   openbuf(umL_FStream* sb, void** sd, void (*free)(void*)
	 *           void* buf, char* outenc, char* inenc)
	 * @endcode
	 * Opens a buffer @c buf, in the encoding @c inenc, and converts its 
	 * contents to the encoding @c outenc. If @c inenc is @c NULL, the 
	 * stream opener tries to guess the content's encoding, and creates a new
	 * stream if it can.
	 * If @c free is given, it'll be a function pointer that'll be called with
	 * on @c buf when the stream is closed.
	 * The opened stream and its data is returned in @c sb and @c sd,
	 * respectively.
	 */
	umL_ACT_OPENBUF,

	/** Format:
	 * @code
	 *   openstream(umL_FStream* nsb, void** nsd, 
	 *              umL_FStream sb, void* sd, char* outenc)
	 * @endcode
	 * Opens a new stream capable of converting the data of another stream
	 * @c sb and convert its output to the encoding @c outenc.
	 * This can be mostly used to create chains of stream converters that can
	 * automatically be able to convert between themselves, with the
	 * disadvantage of not being able to control what types of characters can
	 * be converted.
	 * The opened stream and its data is returned in @c nsb and @c nsd,
	 * respectively.
	 * Conversion between data read from the original stream happens at the
	 * time of the read. All commands from the returned stream are repassed to
	 * the original stream. In other words, @c nsb acts as a proxy (and at the
	 * same time as a "translator") for the stream @c sb. Because of that,
	 * closing the proxy will also close its enclosed stream, in a recursive
	 * action.
	 */
	umL_ACT_OPENSTREAM,

} umL_EStreamOpenerAction;


/*##############################################################################
 *# TYPEDEFS ###################################################################
 *############################################################################*/


/**
 * The character stream converter itself.
 * A character stream converts data in a specific encoding into another. It can
 * read character by character, or a specified number of characters.
 * The function's signature is not pre-defined, and depends heavily on
 * @c action.
 * @arg data The stream data.
 * @arg action The operation to be performed.
 * @see umL_EStreamAction
 */
typedef int (*umL_FStream)(
	void* data,
	umL_EStreamAction action,
	...);

/**
 * A function able to create a stream converter.
 * The function's signature is not pre-defined, and depends heavily on
 * @c action.
 */
typedef int (*umL_FStreamOpener)(
	umL_EStreamOpenerAction action,
	...);


/*##############################################################################
 *# DATA #######################################################################
 *############################################################################*/


/**
 * A @c const array containing all of the default stream openers.
 */
umIDATA const umL_FStreamOpener umL_openers[];


/*##############################################################################
 *# FUNCTIONS ##################################################################
 *############################################################################*/


/**
 * Creates a new stream buffer from a file, using only the global opener
 * registry.
 * Tries to identify the file's encoding by iterating over all registered
 * stream openers.
 */
umIAPI int umL_Stream_openfile(
	void** data,             /**< The returned stream data (as an outarg). */
	umL_FStream* fn,         /**< The returned stream function (as an outarg).*/
	char* filename,          /**< File to be opened. */
	const char* outenc,      /**< The encoding output format. */
	const char* hint);       /**< A hint to the input's encoding. If the
	                              stream can't identify the stream encoding, 
	                              it'll assume the encoding passed. @c hint
	                              must be an ASCII string. */

/** 
 * Creates a new stream reader from a data buffer, using only the global
 * opener registry.
 * The data buffer can be a string or a byte buffer in some specific encoding.
 * Internally, the module will try to find a stream opener that can handle
 * that buffer.
 */
umIAPI int umL_Stream_openbuffer(
	void** data,             /**< The returned stream data (as an outarg). */
	umL_FStream* fn,         /**< The returned stream function (as an outarg).*/
	void* buf,               /**< The data to be worked on. */
	unsigned long int sz,    /**< Size of @c buf, in bytes. */
	const char* outenc,      /**< The encoding output format. Must be either 
	                              @c NULL or an ASCII, @c NULL terminated
	                              string. */
	const char* hint,        /**< A hint to the input's encoding. If the
	                              stream can't identify the stream encoding, 
	                              it'll assume the encoding passed. Can be
	                              either @c NULL or an ASCII, @c NULL
	                              terminated string. */
	void (*free)(void*));    /**< A function to be called with @c buf to free
	                              it. If passed, the free function passed in
	                              this argument will be called when the stream
	                              is closed. */

/**
 * Creates a new stream buffer from another buffer, using only the global
 * opener registry.
 */
umIAPI int umL_Stream_openstream(
	void **data,
	umL_FStream *fn,
	void **odata
	umL_FStream *ofn,
	const char *outenc);


#endif
