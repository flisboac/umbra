
/*

Three distinct sizes for a string:
- SIZE is the actual size, in bytes, of the string.
- CAPACITY is size, in bytes, of the amount of bytes the string can accomodate.
  Generally, SIZE == CAPACITY unless stated otherwise.
- LENGTH is the size, in characters (or character points), in a string.

The following assumptions can be made of strings:
- STRING: A string is represented by `char*`. This does not imply byte or
  multi-byte strings. A string can have fixed increment steps to retrieve a
  element (typecast to a wchar_t to perform pointer arithmetic, or do increments
  6-bytes at a time, for example), or do an unknwon way to retrieve characters.
- CHARACTER POINT: A `long` represents a point, a value that uniquely represents
  a character in its traits environment (in other words, in the encoding
  represented by the trait). For Unicode, for example, this means a grapheme.
  If long is not enough to uniquely represent a character, i guess you have a
  rather big environment to deal with...
- CHARACTER TYPES: Character types are represented by flags in an `unsigned int`
  value. The library makes the assumption that ints are at least 16-bits wide.
  If not, well, sorry...
- CAPACITY AND SIZE: Capacity and size are given in `size_t`.
- POSITION: Due to the nature of this arrangement, character positions in the
  strings are also given in `char*`.
- ABSOLUTE INDEXING: Absolute indexing of string contents, be it in bytes or
  in characters, are given in `size_t`. Indexing, in this context, means
  accessing string data through array indices, like in `str[0]`.
- RELATIVE POSITIONING: Relative positioning, be it in bytes or in characters,
  is given in `ptrdiff_t`.


*/

#ifndef UMBRA_STRING_H_
#define UMBRA_STRING_H_

#include "umbracfg.h"

typedef struct umZ_String umZ_String;
typedef struct umZ_Buffer umZ_Buffer;

struct umZ_String {

    umZ_Stream sd;
    size_t size;
    char *ptr;
    long hash;
    size_t len;
};

struct umZ_Buffer {

    umZ_String str;
    size_t cap;
    um_Bool noresize;
};

#endif
