#ifndef U_NUM_H_
#define U_NUM_H_

typedef enum umN_NumberType {

    umN_INT,
    umN_FLOAT,
    umN_COMPLEX,
    umN_MATRIX,
    umN_RATIO,

    umN_LINT,
    umN_LFLOAT,
    umN_LCOMPLEX,
    umN_LMATRIX,
    umN_LRATIO
} umN_NumberType;

typedef struct umN_Number umN_Number;
typedef struct umN_Int umN_Int;
typedef struct umN_Float umN_Float;
typedef struct umN_Ratio umN_Ratio;
typedef struct umN_Complex umN_Complex;
typedef struct umN_Matrix umN_Matrix;
typedef struct umN_BigInt umN_BigInt;
typedef struct umN_BigFloat umN_BigFloat;
typedef struct umN_BigRatio umN_BigRatio;
typedef struct umN_BigComplex umN_BigComplex;
typedef struct umN_BigMatrix umN_BigMatrix;

struct umN_Int {
    um_Int val;
};

struct umN_Float {
    um_Float val;
};

struct umN_Ratio {
    um_Int num;
    um_Int den;
};

struct umN_Complex {
    um_Float real;
    um_Float imag;
};

typedef struct umN_Matrix_Tuple {

    size_t idx_sz;
    um_Float val;
    size_t *idx;
    umN_Matrix_Tuple *left;
    umN_Matrix_Tuple *right;
} umN_Matrix_Tuple;

/** 
 * The matrix struct. 
 * A matrix will be "hardwiredly" limited to having at last 256 dimensions.
 * The actual size of each dimension is only limited by available memory.
 * One problem, though, is that the @a data array's size must at least fit on a
 * @c size_t variable.
 * A matrix can be represented in three different memory layouts:
 * - Contiguous: The entire array is contiguous in memory, and is implemented
 *      as a gigantic vector array. The advantage is that access to elements
 *      is fast to the point of depending of a single mathematical formula, and
 *      that proper alignment can allow for operation optimizations such as
 *      using SSE and other specialized math operations at CPU level.
 *      Copying is also extremely fast and straightforward.
 *      The disadvantage is that resizing is difficult and costly to implement
 *      as the number of dimensions increases.
 * - Linked: The matrix is composed of sub-matrices, in a linked list
 *      format. This format has the exact opposite traits as the contiguous
 *      format, because while it becomes easier to resize, access can be 
 *      somewhat slower, and CPU optimizations cannot be performed.
 *      Leaf nodes are contiguous matrices, and determining the sizes of all
 *      dimensions require.
 * - Vector: A matrix with a single dimension, implemented as a single vector.
 *      Very useful as leaf nodes for linked matrices, because resizing is
 *      specially simpler.
 * - Tuple: The matrix is implemented as tuples where the last element is the
 *      value, and all the rightmost elements are the indices to that element.
 */
struct umN_Matrix {

    int layout;

    union {
        /* Contiguous */
        struct {
            size_t val_sz; /**< Precalculated number of elements. */
            size_t dim_sz; /**< Number of dimensions. */
            size_t *dim;   /**< Dimensions' sizes. */
            um_Float *val; /**< Elements of the matrix. */
        } cnt;

        /* Linked */
        struct {
            unsigned long int val_sz; /**< Number of matrices in the list. */
            umN_Matrix *val;          /**< List of sub-matrices. */
        } lnk;

        /* Vector */
        struct {
            unsigned long int val_sz; /**< Number of elements in the matrix. */
            um_Float *val;            /**< Elements of the matrix. */
        } vec;

        /* Tuple */
        struct {
            size_t tup_cap;
            size_t tup_sz;
            umN_Matrix_Tuple *tup;
            umN_Matrix_Tuple *root;
        };
    };
};

/* All the long counterparts are to be implemented later. */
struct umN_BigInt {};
struct umN_BigFloat {};
struct umN_BigRatio {};
struct umN_BigComplex {};
struct umN_BigMatrix {};

struct umN_Number {
    char promote;
    umN_NumberType type;
    union {
        umN_Int        *i;
        umN_Float      *f;
        umN_Ratio      *r;
        umN_Complex    *c;
        umN_Matrix     *m;
        umN_BigInt     *li;
        umN_BigFloat   *lf;
        umN_BigRatio   *lr;
        umN_BigComplex *lc;
        umN_BigMatrix  *lm;
    };
};

umIAPI char* umN_convertbase(const char *in, int from, int to);
umIAPI void umN_convertbase_dispose(char* str);

#endif
