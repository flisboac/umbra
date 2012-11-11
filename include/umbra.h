/**
 * @file include/umbra.h
 */

#ifndef UMBRA_H_
#define UMBRA_H_

#include "umbradef.h"
#define um_NOSIZE ((size_t)-1)
#define um_NOCMP (-2)


/*##############################################################################
 * [ ENUMERATIONS ]
 */


typedef enum um_EEcode_ um_EEcode;

enum um_EEcode_ {

	  um_ERREOS = -1 /**< End-of-stream */
	, um_OK = 0      /**< OK. */
	, um_ERROR       /**< Unknown or generic error. */
	, um_ERRMEM      /**< Out of memory */
	, um_ERRSEQ      /**< Syntax or encoding error. */
	, um_ERRCNV      /**< Conversion or transcoding error */
	, um_ERRINV      /**< Invalid arguments */
	, um_ERRIMPL     /**< Not implemented */
	, um_ERRSUPP     /**< Not supported. */
};


/*##############################################################################
 * [ TYPEDEFS AND STRUCTURES ]
 */

typedef um_INTTYPE um_Int;
typedef um_FLOATTYPE um_Float;

typedef struct um_Alloc_ um_Alloc;
typedef struct um_Lock_ um_Lock;
typedef struct um_Sphere_ um_Sphere;

typedef void* (*um_FAlloc)(void* allocp, void* ptr, size_t sz, size_t align);
typedef int (*um_FLock)(void* lockp);

struct um_Alloc_ {

	void* allocp;
	um_FAlloc allocf;
};

struct um_Lock_ {

	void* lockp;
	um_FLock read;
	um_FLock tryread;
	um_FLock write;
	um_FLock trywrite;
	um_FLock unlock;
};

/*##############################################################################
 * [ UTILITY FUNCTIONS ]
 */


#endif
