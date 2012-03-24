#ifndef UMBRADEF_H_
#define UMBRADEF_H_

#include <stddef.h>

#include "umbracfg.h"

/*=============================================================================
 * ENUMERATIONS
 */

typedef enum um_Bool {
	um_False = 0,
	um_True
} um_Bool;

/**
 * An enumeration with all Umbra's error numbers.
 */
typedef enum um_EEcode {
	um_EECODE_NONE = 0,
	um_EECODE_OK,
	um_EECODE_ERROR,
	um_EECODE_MAX
} um_EEcode;

#ifdef __cplusplus
#	define um_EXPORTC       export "C"
#	define um_EXPORTC_BEGIN um_EXPORTC {
#	define um_EXPORTC_END   }
#else
#	define um_EXPORTC_BEGIN
#	define um_EXPORTC_END
#	define um_EXPORTC
#endif

#define um_MAJORBITS 6
#define um_MINORBITS 12
#define um_PATCHBITS 14
#define um_MAJORMASK ((0xffffffffL << (um_MINORBITS + um_PATCHBITS)) & 0xffffffffL)
#define um_MINORMASK (((0xffffffffL << (um_PATCHBITS)) & (~um_MAJORMASK)) & 0xffffffffL)
#define um_PATCHMASK (0xffffffffL & (~(um_MAJORMASK | um_MINORMASK)))
#define um_MAKEVER(major, minor, patch) \
	((((major) << (um_MINORBITS + um_PATCHBITS)) & um_MAJORMASK) | \
	(((minor) << um_PATCHBITS) & um_MINORMASK) | \
	((patch) & um_PATCHMASK)) & 0xffffffffL
#define um_MAJOR(ver) ((ver) & um_MAJORMASK) >> (um_MINORBITS + um_PATCHBITS)
#define um_MINOR(ver) ((ver) & um_MINORMASK) >> (um_PATCHBITS)
#define um_PATCH(ver) ((ver) & um_PATCHMASK)

#ifndef um_STATIC
#	ifdef STATIC
#		define um_STATIC 1
#	else
#		define um_STATIC 0
#	endif
#endif

#ifndef um_DEBUG
#	ifdef DEBUG
#		define um_DEBUG 1
#	else
#		define um_DEBUG 0
#	endif
#endif

#ifndef um_BUILDING
#	ifdef BUILDING
#		define um_BUILDING 1
#	else
#		define um_BUILDING 0
#	endif
#endif

#if um_STATIC
#	if um_BUILDING
#		define um_API   
#		define um_IAPI  static
#		define um_DATA  
#		define um_IDATA 
#	else
#		define um_API   extern
#		define um_IAPI  static
#		define um_DATA  extern
#		define um_IDATA extern
#	endif
#else
#	if um_BUILDING
#		define um_API   
#		define um_IAPI  static
#		define um_DATA  
#		define um_IDATA 
#	else
#		define um_API   extern
#		define um_IAPI  static
#		define um_DATA  extern
#		define um_IDATA extern
#	endif
#endif

/*=============================================================================
 * INTEGERS
 */

#ifndef um_INTTYPE
#	define um_INTTYPE 0
#endif

#if um_INTTYPE == 0
#	define um_TYPE_INT     long int
/*
#	include <limits.h>
#	define um_INTMAX  INT_MAX
#	define um_INTMIN  INT_MIN
#	define um_INTFMT  "%ld"
#	define um_INTNAME um_STRFY(um_INT)
#	define uI(i)      i ## L
*/
#else
#	error Unknown integer type. Check your configuration file!
#endif

/*=============================================================================
 * FLOATS
 * Floats are used for decimal, complex and matrices.
 */

#ifndef um_FLOATTYPE
#	define um_FLOATTYPE 0
#endif

#if um_FLOATTYPE == 0
#	define um_TYPE_FLOAT     double
/*
#	include <limits.h>
#	include <math.h>
#	define um_FLOATMAX  DBL_MAX
#	define um_FLOATMIN  DBL_MIN
#	define um_FLOATDIG  DBL_DIG
#	define um_FLOATEPS  DBL_EPSILON
#	define um_FLOATHUGE HUGE_VAL
#	define um_FLOATNAN  
#	define um_FLOATINF  
#	define um_FLOATNINF 
#	define um_FLOATFMT  "%lf"
#	define um_FLOATNAME um_STRFY(um_FLOAT)
#	define uF(f)        f ## d
*/
#else
#	error Unknown float type. Check your configuration file!
#endif

#endif /* UMBRADEF_H_ */
