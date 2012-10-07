
#ifndef UMBRA_TYPES_H_
#define UMBRA_TYPES_H_

#include "umbracfg.h"

typedef enum umO_ObjectType umO_ObjectType;

enum umO_ObjectType {

    /* Specific-ish */
    umO_OT_NONE = 0,

    /* Numeric */
    umO_OT_NUMBER,

    /* Stream-ish */
    umO_OT_STREAM,
    umO_OT_REGEX,

    /* Special values-ish */
    umO_OT_UNDEF,
    umO_OT_NIL,
    umO_OT_TRUE,
    umO_OT_FALSE,
    umO_OT_ANY,
    umO_OT_ALL,

    /* Generic */
    umO_OT_OBJECT,
    umO_OT_UOBJECT,
    umO_OT_FUNCTION,
    umO_OT_UFUNCTION,

    /* Trickies */
    umO_OT_MAX,
    umO_OT_MASK = 0x0f
};

#endif
