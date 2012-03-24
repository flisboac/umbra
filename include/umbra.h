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
 * STRINGS
 */

typedef um_TYPE_CHAR um_Char;
typedef um_TYPE_CHARINT um_Cint;

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
	um_ENUMBENV_NAME,  /* number typename as a string */
} um_ENumbEnv;

typedef enum um_ENumbRet {
	um_ENUMBRET_OK,
	um_ENUMBRET_INVALID,
	um_ENUMBRET_ERROR,
	um_ENUMBRET_EDOM,
	um_ENUMBRET_ERANGE
} um_ENumbRet;

typedef um_TYPE_INT um_Int;
typedef um_TYPE_FLOAT um_Float;

um_API um_ENumbRet um_Float_info (um_ENumbEnv key, ...);
um_API um_ENumbRet um_Int_info (um_ENumbEnv key, ...);

/*=============================================================================
 * MACHINERY
 */

typedef enum um_EGprop {
	/* ... */
} um_EGprop;

typedef struct um_Machine um_Machine;

um_API um_EEcode umbra_setp(um_EGprop prop, ...);
um_API um_EEcode umbra_getp(um_EGprop prop, ...);
um_API um_Machine* umbra_openfile(const um_Char* filename, int opts);
um_API um_Machine* umbra_openstring(const um_Char* name, const char* code, int opts);
um_API um_EEcode umbra_run(um_Machine* U, long int opts, int argc, char** argv);
um_API const um_Char* um_EEnum_tostring(um_EEcode errnum);

/*=============================================================================
 * OBJECT MODEL
 */

typedef enum um_EType {
	um_ETYPE_UNKNOWN,

	/* Immediate types */
	um_ETYPE_BOOL,
	um_ETYPE_INTEGER,
	um_ETYPE_FLOAT,

	/* Specific types */
	um_ETYPE_DESCRIPTOR,
	um_ETYPE_INSTANCE
};

typedef struct um_Object um_Object;
typedef struct um_Descriptor um_Descriptor;
typedef struct um_Instance um_Instance;


#endif
