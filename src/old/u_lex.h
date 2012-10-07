/**
 * @file u_lex.h
 */

#ifndef U_LEX_H_
#define U_LEX_H_

#include "u_defs.h"
#include "u_lstream.h"

/*##############################################################################
 *# TYPEDEFS ###################################################################
 *############################################################################*/

/**
 * An opaque struct that contains the entire scanning state.
 */
typedef struct umL_State umL_State;


/*##############################################################################
 *# ENUMERATIONS ###############################################################
 *############################################################################*/

/** Represents a token type. */
typedef enum umL_ETokenType {

    /** An invalid token. */
    umL_TOK_ERROR,

    /** A token representing a string. String markers does not make part 
     * of the string at this stage of parsing. */
    umL_TOK_STRING,

    /** Valid identifiers and reserved words. */
    umL_TOK_NAME,

    /** Punctuation. */
    umL_TOK_SYMBOL,

    /** Represents all kids of numbers, on all bases and with exponents. */
    umL_TOK_NUMBER,

    /** A comment. May be multi-line. */
    umL_TOK_COMMENT,

    /** A heredoc. Despite it being just a comment, it has a more
     * important role. Heredocs are put in the AST, and are passed through
     * to the bytecode. */
    umL_TOK_HEREDOC,

    /** An opening bracket, that defines its own scope. */
    umL_TOK_INSCOPE,

    /** A closing bracket, closing the previous @a umL_TOK_INSCOPE. */
    umL_TOK_DESCOPE,

    /** An indentation. */
    umL_TOK_INDENT,

    /** A deindentation. */
    umL_TOK_DEDENT,

    /** One or more newlines. */
    umL_TOK_NEWLINE,

    /** One or more spaces. Tabs are taken as single spaces. */
    umL_TOK_SPACE,

    /** End of file. This marks the end of "tokenizing". */
    umL_TOK_EOF

} umL_ETokenType;

/**
 * An enum containing all the possible number types.
 */
typedef enum umL_ENumberType {

    /**< Identifies a malformed number literal. */
    umL_NUM_NONE,

    /**< Identfies an integer number. */
    umL_NUM_INT,

    /**< Identified a float number. */
    umL_NUM_FLOAT,

    /**< Identifies a ratio number. */
    umL_NUM_RATIO,

    /**< Identifies a complex number. */
    umL_NUM_COMPLEX,
}


/*##############################################################################
 *# STRUCTS ####################################################################
 *############################################################################*/


/** 
 * Represents a number. 
 * This is a struct that represents the number, with all of its
 * components returned as strings, for conversion by later stages.
 */
typedef struct umL_Number {

    umL_ENumberType type;       /**< The number's type. */
    char size;                  /**< Declared size for the number.
                                     Values less than @c 0 are for small
                                     numbers (numbers that can't be promoted to
                                     big numbers), while values greater than
                                     @c 0 are for big numbers. A value equal
                                     to 0 means that the number is a "natural"
                                     one in the sense that it can be promoted
                                     to a long number when needed. */
    short int base;             /**< The number's base. 
                                     The valid range will always be from 2
                                     to 36, unless @c type is umL_NUM_NONE. */
    struct {
        const char *nat;        /**< The number's integer part. This 
                                     contemplates all digits up to either the
                                     fractional point or the exponent. This
                                     value cannot be @c NULL, unless @a type is
                                     @a umL_NUM_NONE. */
        const char *fract;      /**< The number's fractional portion. All digits
                                     after the fractional point are stored in
                                     this string. If a fractional portion is not
                                     given, @c fract will be @c NULL. */
        const char *expn;       /**< The (scientific) exponent of the number.
                                     Exponent is only valid when the base is
                                     either 2, 8, 10 and 16, having a @c NULL
                                     value otherwise. For number base 2, the
                                     exponent's base is 10, and 2 for all
                                     others. This means that a number like
                                     1e10 can be written as 1 * 10^10, but
                                     0x1p10 is 1 * 2^10 instead. */
    } parts[2];                 /**< The parts of the number, as strings.
                                     Later stages are responsible for converting
                                     these string representations as real 
                                     numbers. @c parts is an array because
                                     ratios can be made of
                                     two distinct parts. */
} umL_Number;


/*##############################################################################
 *# FUNCTIONS ##################################################################
 *############################################################################*/

/** 
 * Creates a new Tokenizer state from a stream.
 * The tokenizer won't close the stream when it reaches the end. Instead,
 * the callee should do that.
 */
umIAPI umL_State* umL_State_fromstream(void* streamData, umL_FStream stream);

/** Closes a tokenizer state. */
umIAPI void umL_State_close(umL_State* state);

/** Gets the next token. */
umIAPI umL_ETokenType umL_State_next(umL_State* state);

/** Returns the tokenizer's status. */
umIAPI int umL_State_status(umL_State* state);

/** Returns the current token's starting line number. */
umIAPI long int umL_State_line(umL_State* state);

/** Returns the current token's starting column number. */
umIAPI long int umL_State_column(umL_State* state);

/** Returns the current token's value. */
umIAPI const char* umL_State_value(umL_State* state);

/** Returns the current token's number struct, if the token is a number. */
umIAPI const umL_Number* umL_State_number(umL_State* state);

/** Returns an error message for the last parsing error. */
umIAPI const char* umL_State_message(umL_State* state);

#endif
