#ifndef USCAN_H_
#define USCAN_H_

#include "umbradef.h"

#define umbL_SCANCLS_ALNUM 0x00000000
#define umbL_SCANCLS_ALPHA 0x00000000
#define umbL_SCANCLS_CNTRL 0x00000000
#define umbL_SCANCLS_DIGIT 0x00000000
#define umbL_SCANCLS_GRAPH 0x00000000
#define umbL_SCANCLS_LOWER 0x00000000
#define umbL_SCANCLS_PRINT 0x00000000
#define umbL_SCANCLS_PUNCT 0x00000000
#define umbL_SCANCLS_SPACE 0x00000000
#define umbL_SCANCLS_UPPER 0x00000000
#define umbL_SCANCLS_INPAR 0x00000000
#define umbL_SCANCLS_DEPAR 0x00000000
#define umbL_SCANCLS_NEWLN 0x00000000
#define umbL_SCANCLS_EOF   0x00000000

#define umbL_SCAN_CHAR (-1)
#define umbL_SCAN_WIDE 1

#define umbL_SCANTYPE_INT    0x01
#define umbL_SCANTYPE_LINT   0x02
#define umbL_SCANTYPE_FLOAT  0x03
#define umbL_SCANTYPE_LFLOAT 0x04
#define umbL_SCANTYPE_STRING 0x05
#define umbL_SCANTYPE_NAME   0x06
#define umbL_SCANTYPE_SYMBOL 0x07
#define umbL_SCANTYPE_INPAR  0x08
#define umbL_SCANTYPE_DEPAR  0x09


typedef enum umbL_EScanCmd {
	/* Initializes the stream scanner.
	 * @argin void** newptr 
	 *     A pointer returned by the function. This pointer
	 *     represents the stream scanner's state, and will be passed by further
	 *     calls to the stream function by means of the 'ptr' parameter.
	 */
	umbL_SCANCMD_INIT,
	/* Finalizes the stream scanner. No arguments. */
	umbL_SCANCMD_QUIT,
	/* Tests the next character for equality with a character passed. */
	umbL_SCANCMD_TEST,
	/* Tests the type of the next character. The argument passed will be an
	 * unsigned int that's supposed to have a value masked from the umbSCAN_*
	 * values. The funtion should test for each case, or for cases that makes
	 * sense. */
	umbL_SCANCMD_TYPE,
	/* Returns the next character on the next argument. */
	umbL_SCANCMD_NEXT
} umbL_EScanCmd;

typedef int umbL_scan_f(void* ptr, umbL_EScanCmd cmd, int* arg);

typedef struct umbL_Scanner umbL_Scanner;
typedef struct umbL_Token umbL_Token;
typedef struct umbL_TokenArgs umbL_tokenArgs;

struct umbL_TokenArgs {
	unsigned int size;
	void* ptr;
};

struct umbL_Token {
	unsigned int type;
	umbL_TokenArgs* args;
};

int umbL_addTokenReader();
umbL_Scanner* umbL_openScanner_c(char* encoding, char* filename);
umbL_Scanner* umbL_openScanner_w(char* encoding, wchar_t* filename);
umbL_Token* umbL_firstToken(umbL_Scanner* scanner);
umbL_Token* umbL_nextToken(umbL_Scanner* scanner);
umbL_Token* umbL_previousToken(umbL_Scanner* scanner);
void umbL_closeScanner(umbL_Scanner* scanner);

#endif
