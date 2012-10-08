/**
 * @file umbradef.h
 */

#ifndef UMBRADEF_H_
#define UMBRADEF_H_

#include "umbracfg.h"


/*
 * [ N U M E R I C ] ===========================================================
 * Definitions are guessed from other definitions in "umbracfg.h".
 * All in name of organization.
 */

#ifndef um_INTTYPE
#	define um_INTTYPE um_INT_LONG
#endif

#if um_INTTYPE == um_INT_INT
#	include <limits.h>
#	define um_TYPE_INT int
#	define um_INTMAX   INT_MAX
#	define um_INTMIN   INT_MIN
#	define um_INTSFMT  ""
#	define um_INTFROMA um_atoi
#	define uI(i)       i
#elif um_INTTYPE == um_INT_LONG
#	include <limits.h>
#	define um_TYPE_INT long int
#	define um_INTMAX   INT_MAX
#	define um_INTMIN   INT_MIN
#	define um_INTSFMT  "l"
#	define um_INTFROMA um_atol
#	define uI(i)       i ## L
#elif um_INTTYPE == um_INT_LLONG
#	include <limits.h>
#	define um_TYPE_INT long long int
#	define um_INTMAX   LLONG_MAX
#	define um_INTMIN   LLONG_MIN
#	define um_INTFMT   "ll"
#	define um_INTFROMA um_atoll
#	define uI(i)       i ## LL
#else
#	error Unknown integer type. For now, non-standard types are not allowed.
#endif

#ifndef um_FLOATTYPE
#	define um_FLOATTYPE um_FLOAT_DOUBLE
#endif

#if um_FLOATTYPE == um_FLOAT_FLOAT
#	include <float.h>
#	define um_TYPE_FLOAT   float
#	define um_FLOATMAX     FLT_MAX
#	define um_FLOATMIN     FLT_MIN
#	define um_FLOATDIG     FLT_DIG
#	define um_FLOATEPS     FLT_EPSILON
#	define um_FLOATSFMT    ""
#	define um_FLOATNAME    um_STRFY(um_FLOAT)
#	define um_FLOATFROMA   um_atof
#	define uF(n)           n ## f
#elif um_FLOATTYPE == um_FLOAT_DOUBLE
#	include <float.h>
#	define um_TYPE_FLOAT   double
#	define um_FLOATMAX     DBL_MAX
#	define um_FLOATMIN     DBL_MIN
#	define um_FLOATDIG     DBL_DIG
#	define um_FLOATEPS     DBL_EPSILON
#	define um_FLOATSFMT    "l"
#	define um_FLOATFROMA   um_atod
#	define um_FLOATNAME    um_STRFY(um_FLOAT)
#	define uF(n)           n
#elif um_FLOATTYPE == um_FLOAT_LDOUBLE
#	include <float.h>
#	define um_TYPE_FLOAT   long double
#	define um_FLOATMAX     LDBL_MAX
#	define um_FLOATMIN     LDBL_MIN
#	define um_FLOATDIG     LDBL_DIG
#	define um_FLOATEPS     LDBL_EPSILON
#	define um_FLOATNAME    um_STRFY(um_FLOAT)
#	define um_FLOATFROMA   um_atold
#	define um_FLOATSFMT    "L"
#	define uF(n)           n ## l
#else
#	error Unknown float type. For now, non-standard types are not allowed.
#endif


#define um_FLOATTOA(n, s, sz) snprintf(s, sz, um_FLOATFMT, n)
#define um_INTTOA(n, s, sz)   snprintf(s, sz, um_INTFMT, n)
#define um_INTFMT    "%" um_INTSFMT "d"
#define um_FLOATFMT  "%" um_FLOATSFMT "g"
#define um_INTNAME   um_STRFY(um_TYPE_INT)
#define um_FLOATNAME um_STRFY(um_TYPE_FLOAT)
typedef um_TYPE_INT um_Int;
typedef um_TYPE_FLOAT um_Float;

umAPI int um_atoi(const char *s);
umAPI long int um_atol(const char *s);
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
	umAPI long long int um_atoll(const char *s);
#endif

umAPI float um_atof(const char *s);
umAPI double um_atod(const char *s);
umAPI long double um_atold(const char *s);


#endif
