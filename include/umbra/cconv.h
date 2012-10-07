
#ifndef UMBRA_CCONV_H_
#define UMBRA_CCONV_H_

#include "umbra/types.h"

typedef struct umZ_Cconv umZ_Cconv;
typedef um_EEcode (*umZ_FCconv)(umZ_Cconv *conv);
typedef um_EEcode (*umZ_FCconvOpener)(
    um_Machine *M,
    umZ_Cconv **ret,
    const char *from,
    const char *to);

struct umZ_Cconv {

    um_Bool close;    /** @a um_True to close the converter on the next call. */
    size_t from_size; /** Size of the input buffer, in bytes. */
    size_t to_size;   /** Size of the output buffer, in bytes. */
    char *from;       /** The input buffer. */
    char *to;         /** The output buffer. */
    umZ_FConv conv;   /** The converter interface. */
};

um_API umZ_Cconv umZ_findCconv(um_Machine *U, const char *from, const char *to);
um_API um_EEcode umZ_addCconvOpener(um_Machine *U, umZ_FCconvOpener opener);

#endif
