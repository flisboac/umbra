
#ifndef UMBRA_CTYPE_H_
#define UMBRA_CTYPE_H_

#include "umbracfg.h"
#include "umbra/cconv.h"

#define umZ_ENC_CHAR  "char"  /**< Uses native @c char strings. */
#define umZ_ENC_WIDE  "wide"  /**< Uses native @c wchar_t strings. */
#define umZ_ENC_UMBRA "umbra" /**< Uses umbra's built-in encoding. */

#define umZ_CTYPE (0x2fff) /**< The valid range of ctype flags. */
#define umZ_ALPHA (0x0001) /**< An alphanumeric character. */
#define umZ_DIGIT (0x0002) /**< A digit. */
#define umZ_ALNUM (umZ_ALPHA & umZ_DIGIT)
#define umZ_XDIGT (0x0004) /**< A hexadecimal digit. */
#define umZ_CNTRL (0x0008) /**< A control character. */
#define umZ_GRAPH (0x0010) /**< A graphical character. */
#define umZ_PRINT (0x0020) /**< A printable character. */
#define umZ_PUNCT (0x0040) /**< A punctuation character. */
#define umZ_SPACE (0x0080) /**< A space character, including newlines and tabs. */
#define umZ_NEWLN (0x0100) /**< A newline character. */
#define umZ_UPPER (0x0200) /**< An uppercase letter. */
#define umZ_LOWER (0x0400) /**< A lowercase letter. */
#define umZ_EOS   (0x0800) /**< End-of-stream (file, buffer, string, etc). */
#define umZ_VALID (0x1000) /**< If a character is valid, this MAY BE set if the character is of no other ctype. */
#define umZ_UMBRA (0x2000) /**< A valid Umbra locale character. */

#define umZ_ISCTYPE(t, x) ( ((x) & (t)) != 0 )
#define umZ_ISALPHA(x)    ( umZ_ISCTYPE(umZ_ALPHA, x) )
#define umZ_ISDIGIT(x)    ( umZ_ISCTYPE(umZ_DIGIT, x) )
#define umZ_ISXDIGT(x)    ( umZ_ISCTYPE(umZ_XDIGT, x) ) /**< Implies @c umZ_ISALNUM(x) */
#define umZ_ISALNUM(x)    ( umZ_ISALPHA(x) && umZ_ISDIGIT(x) )
#define umZ_ISCNTRL(x)    ( umZ_ISCTYPE(umZ_CNTRL, x) ) /**< Implies @code !umZ_ISALNUM(x) && !umZ_ISPUNCT(x) @endcode */
#define umZ_ISGRAPH(x)    ( umZ_ISCTYPE(umZ_GRAPH, x) )
#define umZ_ISPRINT(x)    ( umZ_ISCTYPE(umZ_PRINT, x) )
#define umZ_ISPUNCT(x)    ( umZ_ISCTYPE(umZ_PUNCT, x) ) /**< Implies @c !umZ_ISALNUM(x) */
#define umZ_ISSPACE(x)    ( umZ_ISCTYPE(umZ_SPACE, x) )
#define umZ_ISNEWLN(x)    ( umZ_ISCTYPE(umZ_NEWLN, x) ) /**< Implies @c umZ_ISSPACE(x) */
#define umZ_ISUPPER(x)    ( umZ_ISCTYPE(umZ_UPPER, x) ) /**< Implies @c umZ_ISALPHA(x) */
#define umZ_ISLOWER(x)    ( umZ_ISCTYPE(umZ_LOWER, x) ) /**< Implies @c umZ_ISALPHA(x) */
#define umZ_ISVALID(x)    ( umZ_ISANY(x) || umZ_ISCTYPE(umZ_VALID, x) )
#define umZ_ISUMBRA(x)    ( umZ_ISCTYPE(umZ_UMBRA, x) )
#define umZ_ISEOS(x)      ( umZ_ISCTYPE(umZ_EOS,   x) )
#define umZ_ISANY(x)      ( umZ_ISCTYPE(umZ_Ctrait, x) )
#define umZ_ISNONE(x)     !umZ_ISANY(x)


typedef unsigned int umZ_Ctypes;
typedef long umZ_Cpoint;
typedef struct umZ_Ctrait umZ_Ctrait;
typedef enum umZ_ECtraitAction umZ_ECtraitAction;
typedef struct umZ_CtraitArgs umZ_CtraitArgs;
typedef um_EECode (*umZ_FCtrait)(const umZ_Ctrait *trait, umZ_CtraitArgs *args);

enum umZ_ECtraitAction {

    /* Encoding properties */

    umZ_CA_INFO,    /* [self?, minsize, maxsize, eof, other?] info() -- (self = name, other = eof)*/

    /* String and Character Properties */

    umZ_CA_VALID,   /* [] valid(self, pos?, endpos?) */
    umZ_CA_LEN,     /* [length] len(self, pos?, endpos?) */
    umZ_CA_CTYPE,   /* [ctype, point] ctype(self, pos?) */

    /* Character Positioning */

    umZ_CA_FIRST,   /* [pos, endpos, other?] first(self) */
    umZ_CA_LAST,    /* [pos, endpos, other?] last(self) */
    umZ_CA_SEEK,    /* [pos, endpos, other?] seek(self, offset, pos?, endpos?) */
    umZ_CA_POS,     /* [pos, endpos, other?] pos(self, idx, pos?, endpos?) */
    umZ_CA_COLL,    /* [cmp] coll(self, other) */

    /* Conversions */

    umZ_CA_TOSTR,   /* [self] tostr(point) */
    umZ_CA_LOWER,   /* [other ? other : self] lower(self, pos?, endpos?) */
    umZ_CA_UPPER,   /* [other ? other : self] lower(self, pos?, endpos?) */
    umZ_CA_SWAPCASE /* [other ? other : self] lower(self, pos?, endpos?) */
};

struct umZ_CtraitArgs {
    umZ_ECtraitAction action;

    umZ_Cpoint point;   /** A character point to be used in the operation .*/
    umZ_Ctypes ctype;   /** Character types to be considered in the operation.*/
    union {
        ptrdiff_t offset; /** Position offset, in characters. */
        size_t length;    /** Length of the string, in characters. */
        size_t idx;       /** An unsigned position index to the character array.*/
        int cmp;          /** Results of collation and comparison. */
    };
    union {
        size_t self_size;  /** Size of the input string, in bytes. */
        size_t minsize;    /** Minimum size, in bytes, of a character. */
    }
    union {
        size_t other_size; /** Size of other string, in bytes. */
        size_t maxsize;    /** Maximum size, in bytes, of a character. */
    }
    char *pos;          /** Starting position in the input string. */
    char *endpos;       /** End position in the input string. */
    char *other_pos;    /** Starting position in the other string. */
    char *self;         /** The input string. */
    char *other;        /** An other string to be used in the call. */
    const char *name;   /** The trait's name. Has names like "UTF-8". */
};

struct umZ_Ctrait {
    umZ_FCtrait f;      /** The trait interface. */
};

um_API void umZ_initctraitargs(umZ_CtraitArgs *ca);
um_API const umZ_Ctrait *umZ_findctrait(um_Machine *M, const char *enc);
um_API um_EEcode umZ_addctrait(um_Machine *M, const umZ_Ctrait *trait);

#endif
