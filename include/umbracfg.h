/**
 * @file include/umbracfg.h
 */

#ifndef UMBRACFG_H_
#define UMBRACFG_H_

/* 
 * This whole file will be generated by waf, when wscript gets properly written.
 * The thing is, waf is still kind of tricky, and difficult to write correctly!
 * (Or i'm just too lazy to get it done...)
 */


/*
 * [ C O N S T A N T S ] =======================================================
 * Please don't change!
 */


#define um_INT_INT 1
#define um_INT_LONG 2
#define um_INT_LLONG 3
#define um_FLOAT_FLOAT 4
#define um_FLOAT_DOUBLE 5
#define um_FLOAT_LDOUBLE 6
#define um_MAJORBITS 6
#define um_MINORBITS 11
#define um_PATCHBITS 15
#define um_STRQT(s) #s
#define um_STRFY(s) um_STRQT(s)


/*
 * [ C O N F I G ] =============================================================
 * Please change!
 */


#define um_NAME "umbra"/*@@APPNAME@@*/
#define um_VENDOR "vanilla"/*@@VENDORNAME@@*/
#define um_RELEASETYPE "beta"/*@@RELEASETYPE@@*/
#define um_MAJORVERSION (0)/*@@MAJORVERSION@@*/
#define um_MINORVERSION (1)/*@@MINORVERSION@@*/
#define um_PATCHVERSION (0)/*@@PATCHVERSION@@*/
#define um_INTTYPE um_INT_LONG/*@@INTTYPE@@*/
#define um_FLOATTYPE um_FLOAT_DOUBLE/*@@FLOATTYPE@@*/


/*
 * [ V E R S I O N ] ===========================================================
 * Do not change. Don't expect um_VERSION to be endian-independent or
 * exchangeable between different build sessions even on the same target.
 * Still, its use in header files is valid.
 */


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

#define um_VERSION um_MAKEVER(um_MAJORVERSION, um_MINORVERSION, um_PATCHVERSION)

#ifdef um_RELEASETYPE
#   ifdef um_VENDOR
#       define um_RELEASENAME \
            um_VENDOR " " um_NAME " " \
            um_STRFY(um_MAJORVERSION) "." \
            um_STRFY(um_MINORVERSION) "." \
            um_STRFY(um_PATCHVERSION) "-" \
            um_RELEASETYPE
#   else
#       define um_RELEASENAME \
            um_NAME " " \
            um_STRFY(um_MAJORVERSION) "." \
            um_STRFY(um_MINORVERSION) "." \
            um_STRFY(um_PATCHVERSION) "-" \
            um_RELEASETYPE
#   endif
#else
#   ifdef um_VENDOR
#       define um_RELEASENAME \
            um_VENDOR " " um_NAME " " \
            um_STRFY(um_MAJORVERSION) "." \
            um_STRFY(um_MINORVERSION) "." \
            um_STRFY(um_PATCHVERSION)
#   else
#       define um_RELEASENAME \
            um_NAME " " \
            um_STRFY(um_MAJORVERSION) "." \
            um_STRFY(um_MINORVERSION) "." \
            um_STRFY(um_PATCHVERSION)
#   endif
#endif


/*
 * [ M A R K E R S ] ===========================================================
 * Change if you know what you're doing...
 */


#if !defined(um_STATIC) && defined(_WIN32)
#   define um_FIMPORT __declspec(dllimport)
#   define um_FEXPORT __declspec(dllexport)
#   define um_DIMPORT um_FIMPORT
#   define um_DEXPORT um_FEXPORT
#else
#   define um_FIMPORT extern
#   define um_FEXPORT
#   define um_DIMPORT um_FIMPORT
#   define um_DEXPORT
#endif


#ifdef __cplusplus
#	define um_EXPORTC
#	define um_EXPORTC_BEGIN
#	define um_EXPORTC_END
#else
#	define um_EXPORTC export "C"
#	define um_EXPORTC_BEGIN export "C" {
#	define um_EXPORTC_END   }
#endif


#if defined(um_BUILDING)
#   define um_API um_FEXPORT
#   define um_DATA um_DEXPORT
#   if defined(um_STATIC)
#       define um_IAPI static
#       define um_IDATA
#   else
#       if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
                defined(__ELF__)
#           define um_IAPI __attribute__((visibility("hidden"))) extern
#           define um_IDATA um_IAPI
#       else
#           define um_IAPI extern
#           define um_IDATA extern
#       endif
#   endif
#else
#   define um_API um_FIMPORT
#   define um_DATA um_DIMPORT
#endif


#endif
