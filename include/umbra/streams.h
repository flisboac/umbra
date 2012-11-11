/**
 * @file include/umbra/streams.h
 */

#ifndef UMBRA_STREAMS_H_
#define UMBRA_STREAMS_H_

/*##############################################################################
 * [[[   DEFINES   ]]]
 */

#define umS_CTYPE (0x2fff) /**< The valid range of ctype flags. */
#define umS_ALPHA (0x0001) /**< An alphanumeric character. */
#define umS_DIGIT (0x0002) /**< A digit. */
#define umS_XDIGT (0x0004) /**< A hexadecimal digit. */
#define umS_CNTRL (0x0008) /**< A control character. */
#define umS_GRAPH (0x0010) /**< A graphical character. */
#define umS_PRINT (0x0020) /**< A printable character. */
#define umS_PUNCT (0x0040) /**< A punctuation character. */
#define umS_SPACE (0x0080) /**< A space character, including newlines and tabs. */
#define umS_NEWLN (0x0100) /**< A newline character. */
#define umS_UPPER (0x0200) /**< An uppercase letter. */
#define umS_LOWER (0x0400) /**< A lowercase letter. */
#define umS_EOS   (0x0800) /**< End-of-stream (file, buffer, string, etc). */
#define umS_VALID (0x1000) /**< If a character is valid, this MAY BE set if the character is of no other ctype. */
#define umS_SLENC (0x2000) /**< A valid "SL" locale character. */

#define umS_ISCTYPE(t, x) ( ((x) & (t)) != 0 )
#define umS_ISALPHA(x)    ( umS_ISCTYPE(umS_ALPHA, x) )
#define umS_ISDIGIT(x)    ( umS_ISCTYPE(umS_DIGIT, x) )
#define umS_ISXDIGT(x)    ( umS_ISCTYPE(umS_XDIGT, x) ) /**< Implies @c umS_ISALNUM(x) */
#define umS_ISALNUM(x)    ( umS_ISALPHA(x) && umS_ISDIGIT(x) )
#define umS_ISCNTRL(x)    ( umS_ISCTYPE(umS_CNTRL, x) ) /**< Implies @code !umS_ISALNUM(x) && !umS_ISPUNCT(x) @endcode */
#define umS_ISGRAPH(x)    ( umS_ISCTYPE(umS_GRAPH, x) )
#define umS_ISPRINT(x)    ( umS_ISCTYPE(umS_PRINT, x) )
#define umS_ISPUNCT(x)    ( umS_ISCTYPE(umS_PUNCT, x) ) /**< Implies @c !umS_ISALNUM(x) */
#define umS_ISSPACE(x)    ( umS_ISCTYPE(umS_SPACE, x) )
#define umS_ISNEWLN(x)    ( umS_ISCTYPE(umS_NEWLN, x) ) /**< Implies @c umS_ISSPACE(x) */
#define umS_ISUPPER(x)    ( umS_ISCTYPE(umS_UPPER, x) ) /**< Implies @c umS_ISALPHA(x) */
#define umS_ISLOWER(x)    ( umS_ISCTYPE(umS_LOWER, x) ) /**< Implies @c umS_ISALPHA(x) */
#define umS_ISVALID(x)    ( umS_ISANY(x) || umS_ISCTYPE(umS_VALID, x) )
#define umS_ISSLENC(x)    ( umS_ISCTYPE(umS_SLENC, x) )
#define umS_ISEOS(x)      ( umS_ISCTYPE(umS_EOS,   x) )
#define umS_ISANY(x)      ( umS_ISCTYPE(umS_CTYPE, x) )
#define umS_ISNONE(x)     !umS_ISANY(x)


/*##############################################################################
 * [[[   ENUMERATIONS   ]]]
 */

/* Reminder: umS_ENature represents a nature, not a type.
 * The type of a stream is its API. Whether it can be used exchangeably with
 * other APIs based on its nature is implementation-dependent, and therefore,
 * not portable.
 */
typedef enum umS_ENature_ {

	  umS_NAT_NONE   /**< The stream has no specific nature. */
	, umS_NAT_FILTER /**< The stream is a converter between traits. */
	, umS_NAT_BUFFER /**< The stream is buffered. */
	, umS_NAT_FILE   /**< The stream is a file handle. */
	, umS_NAT_STRING /**< The stream implements a string object. */

	/* ... */

	, umS_NAT_MAX
} umS_ENature;


/*##############################################################################
 * [[[   TYPE DEFINITIONS   ]]]
 */


/* Immediate types */
typedef unsigned int umS_Ctypes;      /**< An integer with flags describing a character's types. */
typedef long int umS_Cpoint;          /**< An encoding's code point. */
typedef long int umS_Off;             /**< A type representing an offset starting from a position. */

/* Base types */
typedef struct umS_Ctrait_ umS_Ctrait; /**< The encoding itself. */
typedef struct umS_Cconv_ umS_Cconv;   /**< An encoding conversion object. */

/* Environment */
typedef struct umS_Stream_ umS_Stream; /**< The base stream object. */
typedef struct umS_Pos_ umS_Pos;       /**< An object representing a position inside a stream. */

/* Streams */
typedef struct umS_StreamApi_ umS_StreamApi;
typedef struct umS_State_ umS_State;
typedef struct umS_Opts_ umS_Opts;

/* Function signatures */
typedef int (*umS_FEvent)(void* state, um_EEcode ecode, umS_Stream* S, umS_Pos* P);
typedef umS_Cconv* (*umS_FOpenconv)(umS_Ctrait* from, umS_Ctrait* to, umS_FAlloc allocf, void* allocp);


/*##############################################################################
 * [[[   BASIC STRUCTS AND UNIONS   ]]]
 */


struct umS_Cconv_ {

	umS_Ctrait* from_enc;
	umS_Ctrait* to_enc;
	const char* from;
	char* to;
	char* from_pos;
	char* to_pos;
	size_t from_sz;
	size_t to_sz;

	um_EEcode (*step)(umS_Cconv* conv, size_t step);
	um_EEcode (*dispose)(umS_Cconv* conv);
};


/*
 * All functions in a character trait should be reentrant, and do what they can
 * to not introduce side-effects. A character trait is about how the binary
 * stream is organized, it should not use any global state or call
 * non-reentrant functions.
 */
struct umS_Ctrait_t {

	const umS_Ctrait *base;
	const char* name;
    const size_t minsize;
    const size_t maxsize;
    const umS_Cpoint eof;

    /* Seeks `off` characters in a buffer `s` of size `sz`,
     * starting from the position `*pos`. If `*pos` is null, it's assumed to
     * start from the beginning of the buffer, and if off is negative in this
     * case, the search is backwards and starts from the end of the stream.
     * At the end of the process, the number of bytes for the character found
     * will be returned, or 0 if no character was found.
     * `pos` is allowed to point to the same initial string as `s`, and the
     * function must identify it appropriately.
     * `pos` and `s` cannot be null.
     * - The first character could be written as `seek(T, s, sz, 0, NULL)`
     * - The next character could be written as `seek(T, s, sz, 1, NULL)`
     * - The last character could be written as `seek(T, s, sz, -1, NULL)`
     * - validchar check could be written as `seek(T, s, maxsize, 0, NULL) != NULL`
     * - size of string can be computed as sequenced calls to the function,
     *   one character at a time, until no character is read.
     *   (considering s has maxsize bytes)
     */
    size_t (*seek)(umS_Ctrait* T, char *s, size_t sz, umS_Off off, char **pos);

    /* Gets the equivalent cpoint for the next character.
     * Returns umS_NOPOINT on error. */
    umS_Cpoint (*cpoint)(umS_Ctrait* T, char *s, size_t sz);

    /* Transforms the code point into a string.
	 * s must be a pre-allocated buffer with at least minsize bytes.
     * Returns umS_INVALIDSIZE in case of error.
     * If s is NULL, the function simply returns the number of bytes
     * required for storing the character. */
    size_t (*tostr)(umS_Ctrait* T, umS_Cpoint cpoint, char *s, size_t sz);

    /* Gets all valid ctypes for the character point passed. */
    umS_Ctypes (*ctypes)(umS_Ctrait* T, umS_Cpoint cpoint);

    /* tolower, toupper */
    umS_Cpoint (*tolower)(umS_Ctrait* T, umS_Cpoint cpoint);
    umS_Cpoint (*toupper)(umS_Ctrait* T, umS_Cpoint cpoint);

    /* Compares two strings. Translates characters if needed.
     */
    int (*compare)(umS_Ctrait* T, const char* a, size_t a_sz, const char* b, size_t b_sz);

    /* Transforms the string such that it can be safely compared
     * lexicographically. The result is a binary-safe string that can be used
     * to compare between another transformed string without having to translate
     * characters or worry about encoding issues (like multi-byte, etc).
     * Note that transformed strings must only be compared with other
     * transformed strings of the same character trait.
     * If to is null or if to_sz is 0, the function simply returns the number
     * of bytes that the transformed string would require.
     */
    size_t (*transform)(umS_Ctrait* T, const char* from, size_t from_sz, char* to, size_t to_sz);
};


struct umS_Stream_ {

	umS_StreamApi *api;
	um_EEcode ecode;
	umS_Ctrait *enc;    /**< The stream's encoding. If it has no encoding,
	                        the stream is considered to be binary (instead
	                        of text-based), and reads-writes are in terms
	                        of bytes (instead of characters). */
};


struct umS_Pos_ {

    umS_Stream *S;  /**< The stream from where this position was originated.
                        Positions are not exchangeable between different stream
                        instances, even if they're of the same type. */
    int aligned;   /**< If 1, the position is character-aligned.
                        Positions are always given in bytes, but if this flag is
                        set, the position is in a character boundary, meaning
                        that the position is right after a previous character
                        (considering that it's not set to the start of the
                        stream, in which case it's always considered to be
                        aligned). */

    void (*dispose)(umS_Pos* pos);
};


struct umS_Opts_ {

	/* Basic */
	umS_FAlloc allocf;
	void* allocp;
	umS_FEvent eventf;
	void* eventp;
	const char* mode; /**< The operational mode. */
};


struct umS_StreamApi_ {


	/*
	 * Implementation details.
	 */

	umS_StreamApi *base;
	const char* implname;
	const umS_ENature* (*getnatures)(umS_StreamApi *A);
	void** (*getnatureapis)(umS_StreamApi *A);

	/*
	 * Creation and disposal.
	 */

	umS_Stream* (*openwith)(umS_StreamApi *A, umS_Opts* opts);
	umS_Stream* (*reopen)(umS_StreamApi *A, umS_Stream* S, umS_Opts* opts);
	um_EEcode (*close)(umS_StreamApi *A, umS_Stream* S);

	/*
	 * Read/Write.
	 * sz is the size of the buffer buf, in bytes.
	 * nchars indicates the number of characters to read or write.
	 * If nchars == 0, this indicates a binary read, disregarding the
	 * encoding of the stream, and buf will be filled with sz bytes.
	 * If nchars == umS_NOSIZE, it tries to read all available characters
	 * from the stream, up until an error condition is met, like
	 * end-of-stream or invalid sequences.
	 * The value returned is either the number of characters or bytes read,
	 * depending on the value of nsize, as described earlier.
	 */

	size_t (*read)(umS_StreamApi *A, umS_Stream* S, char* buf, size_t sz, size_t nchars);
	size_t (*write)(umS_StreamApi *A, umS_Stream* S, char* buf, size_t sz, size_t nchars);

	/*
	 * Positioning
	 */

	umS_Pos* (*getpos)(umS_StreamApi *A, umS_Stream* S);
	um_EEcode (*setpos)(umS_StreamApi *A, umS_Stream* S, umS_Pos* pos);
	um_EEcode (*tell)(umS_StreamApi *A, umS_Stream* S, umS_Off* off);
	um_EEcode (*seek)(umS_StreamApi *A, umS_Stream* S, umS_Off off, int where);
};


/*##############################################################################
 * [[[   VARIABLES   ]]]
 */




/*##############################################################################
 * [[[   FUNCTIONS   ]]]
 */



um_API void umS_Pos_dispose(umS_Pos* pos);

um_API um_EEcode umS_Cconv_step(umS_Cconv* conv, size_t step);
um_API um_EEcode umS_Cconv_dispose(umS_Cconv* conv);

um_API size_t umS_Ctrait_seek(umS_Ctrait* T, char *s, size_t sz, umS_Off off, char **pos);
um_API umS_Cpoint umS_Ctrait_cpoint(umS_Ctrait* T, char *s, size_t sz);
um_API size_t umS_Ctrait_tostr(umS_Ctrait* T, umS_Cpoint cpoint, char *s, size_t sz);
um_API umS_Ctypes umS_Ctrait_ctypes(umS_Ctrait* T, umS_Cpoint cpoint);
um_API umS_Cpoint umS_Ctrait_tolower(umS_Ctrait* T, umS_Cpoint cpoint);
um_API umS_Cpoint umS_Ctrait_toupper(umS_Ctrait* T, umS_Cpoint cpoint);
um_API int umS_Ctrait_compare(umS_Ctrait* T, const char* a, size_t a_sz, const char* b, size_t b_sz);
um_API size_t umS_Ctrait_transform(umS_Ctrait* T, const char* from, size_t from_sz, char* to, size_t to_sz);

#endif /* UMBRA_STREAMS_H_ */
