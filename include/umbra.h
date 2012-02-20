/*
 * This file contains Umbra's external API.
 */

#ifndef UMBRA_H_
#define UMBRA_H_

#include <stdarg.h>
#include <stddef.h>

#include "umbradef.h"

/*=============================================================================
 * DEFINES
 */

#define um_NAME uS("Umbra")
#define um_MAJORVERSION 0
#define um_MINORVERSION 1
#define um_PATCHVERSION 0
#define um_VERSION um_MAKEVER(um_MAJORVERSION, um_MINORVERSION, um_PATCHVERSION)

/* Defining the release name */
#ifdef um_RELEASETYPE
#	ifdef um_VENDOR
#		define um_RELEASENAME uS(" ") \
			um_VENDOR uS(" ") um_NAME uS(" ") \
			um_STRFY(um_MAJORVERSION) uS(".") \
			um_STRFY(um_MINORVERSION) uS(".") \
			um_STRFY(um_PATCHVERSION) uS("-") \
			um_RELEASETYPE
#	else
#		define um_RELEASENAME uS(" ") \
			um_NAME uS(" ") \
			um_STRFY(um_MAJORVERSION) uS(".") \
			um_STRFY(um_MINORVERSION) uS(".") \
			um_STRFY(um_PATCHVERSION) uS("-") \
			um_RELEASETYPE
#	endif
#else
#	ifdef um_VENDOR
#		define um_RELEASENAME uS(" ") \
			um_VENDOR uS(" ") um_NAME uS(" ") \
			um_STRFY(um_MAJORVERSION) uS(".") \
			um_STRFY(um_MINORVERSION) uS(".") \
			um_STRFY(um_PATCHVERSION)
#	else
#		define um_RELEASENAME uS(" ") \
			um_NAME uS(" ") \
			um_STRFY(um_MAJORVERSION) uS(".") \
			um_STRFY(um_MINORVERSION) uS(".") \
			um_STRFY(um_PATCHVERSION)
#	endif
#endif

/*=============================================================================
 * ENUMERATIONS
 */

typedef enum um_Bool {
	um_False = 0,
	um_True
} um_Bool;

typedef enum um_EType {
	um_ETYPE_UNKNOWN,    /* When an error occurs... */

	/* Immediate types */
	um_ETYPE_BOOL,       /* Generally a 'unsigned char' */
	um_ETYPE_INTEGER,    /* Generally a 'long int */
	um_ETYPE_FLOAT,      /* Generally a 'double' */

	/* Specific types */
	um_ETYPE_DESCRIPTOR, /* Classes, interfaces, mixins. The specific sub-type
	                     /  must be queried through specialized functions.
	                     /  Packages and methods are specialized versions of
	                     /  descriptors. Specially, a descriptor is merely a
	                     /  wrapper around real code blocks (umi_Runner). */
	um_ETYPE_INSTANCE    /* Instances of descriptors. Generally, all
	                     /  objects that are not either a descriptor or
	                     /  a native type are merely instances. */
};

typedef enum um_EGprop {
	/* ... */
} um_EGprop;

/*
 * - Float types must fail on the binary operations. 
 * - Integers should fail on some of the math operations.
 * - The elemental operators are so trivial to implement, but depending
 *   on the number type, some kind of optimization could be used.
 *   Still, they're just numbers, and normal operators can be used (as long
 *   as the operands are of the same type).
 */
typedef enum um_ENumbOp {
	/* Elementary math operations */
	um_ENUMBOP_ADD,
	um_ENUMBOP_SUB,
	um_ENUMBOP_MUL,
	um_ENUMBOP_DIV,
	um_ENUMBOP_REM,
	um_ENUMBOP_MINUS,
	um_ENUMBOP_DEC,
	um_ENUMBOP_INC,
	
	/* Comparison */
	um_ENUMBOP_CMP,
	
	/* Conversion */
	um_ENUMBOP_TOFLOAT,
	um_ENUMBOP_TOINT,
	um_ENUMBOP_FROMCSTR,
	um_ENUMBOP_FROMWSTR,
	um_ENUMBOP_TOCSTR,
	um_ENUMBOP_TOWSTR,
	
	/* Binary */
	um_ENUMBOP_SHL,  /* Shift left */
	um_ENUMBOP_SHR,  /* Shift right */
	um_ENUMBOP_SSHL, /* Signed shift left */
	um_ENUMBOP_SSHR, /* Signed shift right */
	um_ENUMBOP_AND,  /* Binary AND */
	um_ENUMBOP_OR,   /* Binary OR */
	um_ENUMBOP_XOR,  /* Binary XOR */
	um_ENUMBOP_CPL,  /* Binary complement */
	
	/* Math operations, as in math.h/stdlib.h */
	um_ENUMBOP_COS,
	um_ENUMBOP_SIN,
	um_ENUMBOP_TAN,
	um_ENUMBOP_ACOS,
	um_ENUMBOP_ASIN,
	um_ENUMBOP_ATAN,
	um_ENUMBOP_ATAN2,
	um_ENUMBOP_COSH,
	um_ENUMBOP_SINH,
	um_ENUMBOP_TANH,
	um_ENUMBOP_CEIL,
	um_ENUMBOP_FLOOR,
	um_ENUMBOP_SQRT,
	um_ENUMBOP_POW,
	um_ENUMBOP_EXP,
	um_ENUMBOP_LOG,
	um_ENUMBOP_LOG10,
	um_ENUMBOP_MOD,
	um_ENUMBOP_ABS
} um_ENumbOp;

typedef enum um_ENumbEnv {
	um_ENUMBENV_MIN,   /* Minimum value */
	um_ENUMBENV_MAX,   /* Maximum value */
	um_ENUMBENV_EPS,   /* Epsilon */
	um_ENUMBENV_DIG,   /* Digits */
	um_ENUMBENV_FMT,   /* printf format, if any */
	um_ENUMBENV_HUGE,  /* Huge val */
	um_ENUMBENV_NAN,   /* not a number value */
	um_ENUMBENV_INF,   /* infinte value */
	um_ENUMBENV_NINF,  /* negative infinte value */
	um_ENUMBENV_SIZE,  /* sizeof, in (CHAR_BIT) bytes */
	um_ENUMBENV_CNAME, /* number typename as a char string */
	um_ENUMBENV_WNAME  /* number typename as a wide string */
} um_ENumbEnv;

typedef enum um_ENumbRet {
	um_ENUMBRET_OK,
	um_ENUMBRET_INVALID,
	um_ENUMBRET_ERROR,
	um_ENUMBRET_EDOM,
	um_ENUMBRET_ERANGE
} um_ENumbRet;

/**
 * An enumeration with all Umbra's error numbers.
 */
typedef enum um_EEcode {
	um_EECODE_NONE = 0,
	um_EECODE_OK,
	um_EECODE_ERROR,
	um_EECODE_MAX
} um_EEcode;

/*=============================================================================
 * STRINGS
 */

typedef um_CHAR um_Char;
typedef um_CHARINT um_Cint;

um_API um_EEcode um_Char_tocstring(const um_Char* from, char* to, size_t to_sz);
um_API um_EEcode um_Char_towstring(const um_Char* from, wchar_t* to, size_t to_sz);

um_API um_Char* um_Char_fromcstring(const char* str);
um_API um_Char* um_Char_fromwstring(const wchar_t* str);
um_API um_Char* um_Char_new();
um_API um_Char* um_Char_newsz(size_t sz);
um_API um_Char* um_Char_dup(const um_Char* str);
um_API void um_Char_delete(um_Char* str);

/*=============================================================================
 * NUMBERS
 */

typedef um_INT um_Int;
typedef um_FLOAT um_Float;
typedef um_Int (*um_FIntDo) (um_ENumbOp operation, um_ENumbRet *result, ...);
typedef um_Float (*um_FFloatDo) (um_ENumbOp operation, um_ENumbRet *result, ...);

um_API um_ENumbRet um_Float_get (um_ENumbEnv key, ...);
um_API um_ENumbRet um_Int_get (um_ENumbEnv key, ...);

/*=============================================================================
 * MACHINERY
 */

/* An object can be anything, from a simple integer up to a descriptor. */
typedef struct um_Object um_Object;

/* A descriptor represents an entity, that can be a class, package,
 * method, etc. It is, in itself and implicitly, an instance of Object (that
 * is, in turn, a descriptor).
 */
typedef struct um_Descriptor um_Descriptor;

/* An instance is always associated with a descriptor. It represents all
 * instantiated objects, or entities that cannot be represented by a
 * descriptor. */
typedef struct um_Instance um_Instance;

/* A machine is a state. It contains its own stack and can spawn runners
 * (code to be executed).
 */
typedef struct um_Machine um_Machine;

um_API um_Machine* umbra_openfile(const um_Char* filename, int opts);
um_API um_Machine* umbra_openstring(const um_Char* name, const char* code, int opts);
um_API um_EEcode umbra_run(um_Machine* U, long int opts, int argc, char** argv);

/*=============================================================================
 * (PROCESS) ENVIRONMENT
 */

um_API int umbra_init(void);
um_API int umbra_quit(void);
um_API int umbra_setp(um_EGprop prop, ...);
um_API int umbra_getp(um_EGprop prop, ...);

/*=============================================================================
 * UTILITIES
 */

um_API const um_Char* um_EEnum_tostring(um_EEcode errnum);

#endif
