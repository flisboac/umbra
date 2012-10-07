#ifndef UMBRADEF_H_
#define UMBRADEF_H_

#include <stddef.h>

#include "umbraver.h"

/*=============================================================================
 * DEFINES
 */

#define um_INT_SPECIFIC 0
#define um_INT_INT 1
#define um_INT_LONG 2
#define um_FLOAT_SPECIFIC 0
#define um_FLOAT_FLOAT 1
#define um_FLOAT_DOUBLE 2
#define um_FLOAT_LDOUBLE 3

#ifdef __cplusplus
#	define um_EXPORTC       export "C"
#	define um_EXPORTC_BEGIN um_EXPORTC {
#	define um_EXPORTC_END   }
#else
#	define um_EXPORTC_BEGIN
#	define um_EXPORTC_END
#	define um_EXPORTC
#endif


#ifdef STATIC
#	define um_STATIC 1
#else
#	define um_STATIC 0
#endif

#ifdef DEBUG
#	define um_DEBUG 1
#else
#	define um_DEBUG 0
#endif

#ifdef BUILDING
#	define um_BUILDING 1
#else
#	define um_BUILDING 0
#endif

/**
 * @class Test
 * An enumeration with all Umbra's error numbers.
 */
enum um_EEcode {
	um_EOS = -1, /** End of stream, file, string or operation. */
	um_OK,       /** Successful operation. */
	um_ERROR,    /** An unknown error. */
	um_ERRSUP,   /** Operation not supported. */
	um_ERRMEM,   /** Not enough memory. */
	um_ERRINVAL, /** Invalid state or arguments. */
	um_ERRDOM,   /** Domain or range error. */
	um_ERRSYN,   /** Syntax error. */
	um_ERRCNV,   /** Conversion error. */
	um_ERRENC,   /** Encoding error. */
	um_ERRMAX    /** Maximum error code, doesn't represent an error. */
};

enum um_ELockAction {

	um_LA_READ,
	um_LA_TRYREAD,
	um_LA_WRITE,
	um_LA_TRYWRITE
};

enum um_EInputFormat {

	um_IF_UNKNOWN = 0,
	um_IF_SOURCE,
	um_IF_BYTECODE,
	um_IF_AST
};

enum um_Bool {
	um_False = 0,
	um_True
};

typedef struct um_Machine um_Machine;
typedef enum um_Bool um_Bool;
typedef enum um_EEcode um_EEcode;
typedef enum um_ELockAction um_ELockAction;
typedef enum um_EInputFormat um_EInputFormat;

typedef um_EEcode (*um_FAlloc)(
	void *ptr,
	void **obj,
	size_t oldsz,
	size_t newsz,
	unsigned int alignment);

typedef um_EEcode (*um_FCfunction)(um_Machine *M);
typedef void (*um_FLock)(um_Machine *M, void *ptr, um_ELockAction action);
typedef um_EEcode (*um_FBuffer)(void *data, char *ptr, long *ptrsz);

#endif /* UMBRADEF_H_ */
