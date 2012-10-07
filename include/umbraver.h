#ifndef UMBRAVER_H_
#define UMBRAVER_H_

#define um_NAME "Umbra"
#define um_MAJORVERSION 0
#define um_MINORVERSION 1
#define um_PATCHVERSION 0

#ifndef um_STRQT
#	define um_STRQT(s) #s
#endif
#ifndef um_STRFY
#	define um_STRFY(s) um_STRQT(s)
#endif

#define um_MAJORBITS 6
#define um_MINORBITS 11
#define um_PATCHBITS 15
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

/* Defining the release name */
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

#endif
