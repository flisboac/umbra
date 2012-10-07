/**
 * @file u_ctype.h
 */

#ifndef U_CTYPE_H_
#define U_CTYPE_H_

/*##############################################################################
 *# DEFINES AND MACROS #########################################################
 *############################################################################*/

/*
 * The library won't use all of these flags. They're all given for completion.
 * Other add-on modules (like a regex module) can use the rest of the flags.
 * The lexer itself will ignore cntrl, print, punct and graph.
 */

#define umL_EOS    um_EOS     /**< End-of-file or stream reached. */
#define umL_OK     um_OK      /**< No errors reported. */
#define umL_ERROR  um_ERROR   /**< An unknown or internal error ocurred. */
#define umL_ERRSUP um_ERRSUP  /**< Unsupported action or operation. */
#define umL_ERRMEM um_ERRMEM  /**< Not enough memory. */
#define umL_ERRSYN um_ERRSYN  /**< Syntax error. */
#define umL_ERRCNV um_ERRCONV /**< Conversion error. Source is somehow badly formed. */
#define umL_ERRENC um_ERRENC  /**< Source is in another encoding. */

#define umL_ENC_CHAR  "char"  /**< Uses native @c char strings. */
#define umL_ENC_WIDE  "wide"  /**< Uses native @c wchar_t strings. */
#define umL_ENC_UMBRA "umbra" /**< Uses umbra's built-in encoding. */

#define umL_CTYPE (0x2fff) /**< The valid range of ctype flags. */
#define umL_ALPHA (0x0001) /**< An alphanumeric character. */
#define umL_DIGIT (0x0002) /**< A digit. */
#define umL_XDIGT (0x0004) /**< A hexadecimal digit. */
#define umL_CNTRL (0x0008) /**< A control character. */
#define umL_GRAPH (0x0010) /**< A graphical character. */
#define umL_PRINT (0x0020) /**< A printable character. */
#define umL_PUNCT (0x0040) /**< A punctuation character. */
#define umL_SPACE (0x0080) /**< A space character, including newlines and tabs. */
#define umL_NEWLN (0x0100) /**< A newline character. */
#define umL_UPPER (0x0200) /**< An uppercase letter. */
#define umL_LOWER (0x0400) /**< A lowercase letter. */
#define umL_EOS   (0x0800) /**< End-of-stream (file, buffer, string, etc). */
#define umL_VALID (0x1000) /**< If a character is valid, this MAY BE set if the character is of no other ctype. */
#define umL_UMBRA (0x2000) /**< A valid Umbra locale character. */

#define umL_ISCTYPE(t, x) ( ((x) & (t)) != 0 )
#define umL_ISALPHA(x)    ( umL_ISCTYPE(umL_ALPHA, x) )
#define umL_ISDIGIT(x)    ( umL_ISCTYPE(umL_DIGIT, x) )
#define umL_ISXDIGT(x)    ( umL_ISCTYPE(umL_XDIGT, x) ) /**< Implies @c umL_ISALNUM(x) */
#define umL_ISALNUM(x)    ( umL_ISALPHA(x) && umL_ISDIGIT(x) )
#define umL_ISCNTRL(x)    ( umL_ISCTYPE(umL_CNTRL, x) ) /**< Implies @code !umL_ISALNUM(x) && !umL_ISPUNCT(x) @endcode */
#define umL_ISGRAPH(x)    ( umL_ISCTYPE(umL_GRAPH, x) )
#define umL_ISPRINT(x)    ( umL_ISCTYPE(umL_PRINT, x) )
#define umL_ISPUNCT(x)    ( umL_ISCTYPE(umL_PUNCT, x) ) /**< Implies @c !umL_ISALNUM(x) */
#define umL_ISSPACE(x)    ( umL_ISCTYPE(umL_SPACE, x) )
#define umL_ISNEWLN(x)    ( umL_ISCTYPE(umL_NEWLN, x) ) /**< Implies @c umL_ISSPACE(x) */
#define umL_ISUPPER(x)    ( umL_ISCTYPE(umL_UPPER, x) ) /**< Implies @c umL_ISALPHA(x) */
#define umL_ISLOWER(x)    ( umL_ISCTYPE(umL_LOWER, x) ) /**< Implies @c umL_ISALPHA(x) */
#define umL_ISVALID(x)    ( umL_ISANY(x) || umL_ISCTYPE(umL_VALID, x) )
#define umL_ISUMBRA(x)    ( umL_ISCTYPE(umL_UMBRA, x) )
#define umL_ISEOS(x)      ( umL_ISCTYPE(umL_EOS,   x) )
#define umL_ISANY(x)      ( umL_ISCTYPE(umL_Ctrait, x) )
#define umL_ISNONE(x)     !umL_ISANY(x)


/*##############################################################################
 *# TYPEDEFS ###################################################################
 *############################################################################*/

typedef unsigned int umL_Ctypes;
typedef long umL_Cpoint;


typedef enum umL_EOper {

	/* Operations */

	umL_OP_CONV,    /* conv(char **ret, const char *src) */

	/* String Properties */
#if 0
	/* (Maybe not needed, the ctype function itself dictates the type,
	 * encoding and limits. */
	umL_OP_ENC,     /* enc(const char **ret) */
	umL_OP_LIMITS,  /* limits(int *ret_min, int *ret_max) */
	umL_OP_EOF,
#endif
	umL_OP_LEN,     /* len(unsigned long *ret, char **next) */

	/* Character properties */

	umL_OP_CTYPE,   /* ctype(unsigned int *ret) */
	umL_OP_CTYPEAT, /* ctype(char* ptr, unsigned int *ret) */
	umL_OP_CPOINT,  /* char(long *ret) */
	umL_OP_CPOINTAT,/* char(char* pos, long *ret) */

	/* Positioning */

	umL_OP_FIRST,   /* begin(char** ret) */
	umL_OP_LAST,    /* end(char** ret) */
	umL_OP_SEEK,    /* seek(char* pos, int offset, char** ret) */
	umL_OP_POS,     /* pos(long offset, char** ret) */
	umL_OP_CHARSZ,  /* charsz(char* pos, size_t *ret) */
	umL_OP_COLL,    /* cmp(char *other, size_t other_sz, int* ret) */

	umL_OP_LOWER,
	umL_OP_UPPER,
	umL_OP_SWAPCASE

} umL_EOper;

typedef struct umL_Ctrait umL_Ctrait;
typedef int umL_FOper(umL_Ctrait trait, umL_EOper oper, ...);

struct umL_Ctrait {
	umL_FOper f; /** The trait interface. */
	void *data;  /** Arbitrary data used by the trait object.
	                 May be used or not by the trait implementation. */
};

/*##############################################################################
 *# DATA #######################################################################
 *############################################################################*/


umIAPI const umL_Ctypes umL_umbratable[257];


/*##############################################################################
 *# FUNCTIONS ##################################################################
 *############################################################################*/


umIAPI umL_Ctypes umL_asciictype(int c);
umIAPI umL_Ctypes umL_umbractype(int c);

umIAPI umL_Ctrait *umL_Ctrait_open(const char *enc);
umIAPI void umL_Ctrait_close(umL_Ctrait *facet);
umIAPI um_Bool umL_Ctrait_equals(umL_Ctrait *self, const umL_Ctrait *other);
umIAPI const char *umL_Ctrait_enc(umL_Ctrait *self);
umIAPI int umL_Ctrait_mincharsz(umL_Ctrait *self);
umIAPI int umL_Ctrait_maxcharsz(umL_Ctrait *self);
umIAPI umL_Cpoint umL_Ctrait_eof(umL_Ctrait *self);

#endif

