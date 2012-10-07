

#ifndef U_STR_H_
#define U_STR_H_

#include <stddef.h>
#include "u_defs.h"
#include "u_ctype.h"

/**
 * The string object.
 * This is a pretty simple interface, with some pre-calculated values.
 * All string functions assumes that the string object won't change its
 * contents, just as what happens in the language (Umbra, that is).
 * If the contents of the string change in any way, the user must recalculate
 * the length and hash properties, and always make @c size be equal to the
 * correct total byte size of the string.
 * The character trait interface @c f should never change. To get a string
 * in another encoding, convert it properly.
 * Another thing to note is that the string object may have embedded nulls, but
 * for it to work correctly with other string libraries, it will always be
 * terminated with a null character by the string yielding functions, despite
 * having its own notion of size. Collation won't work correctly if the string
 * has embedded nulls as well.
 * Unless otherwise stated, string length means character length, string size
 * means byte size, and string capacity means maximum byte length.
 */
typedef struct umS_String {

	size_t size;       /**< The string's size, in bytes. */
	unsigned long len; /**< The string's character length. */
	long hash;         /**< The string's hash code, @c 0 if not calculated. */
	char *cptr;        /**< The string itself. */
	umL_Ctrait *t;     /**< The string's character traits. */
	
} umS_String;


/**
 * Constructs a new string from a (locale's) @c char string.
 */
umIAPI umS_String *umS_String_fromcstr(
	const char* cstr);

/**
 * Constructs a new string from a (locale's) @c wchar_t string.
 */
umIAPI umS_String *umS_String_fromwstr(
	const wchar_t* wstr);

/**
 * A simple copy constructor.
 * This function does nothing more than simply copying the string's contents,
 * byte by byte.
 */
umIAPI umS_String *umS_String_from(
	const umS_String* other);

/**
 * Disposes a string.
 * Just be sure it's not being used anywhere else...
 */
umIAPI void umS_String_dispose(umS_String* self);

/**
 * Gets the character type of the first character in the string.
 */
umIAPI unsigned int umS_String_ctype(const umS_String* self);

/**
 * Gets the character type of the character at the position passed.
 */
umIAPI unsigned int umS_String_ctypeat(
	const umS_String *self,
	char *pos);

/**
 * Gets the first character of the string.
 */
#define umS_String_char(self) umS_String_slice(self, NULL, 1)

/**
 * Gets a string's character at the position passed.
 */
#define umS_String_charat(self, off) umS_String_slice(self, off, 1)

/**
 * Inserts the string @c other at the position passed.
 */
#define umS_String_insert(self, other, pos) umS_String_put(self, other, pos, 0)

/**
 * Removes a sized portion of a string at the position passed.
 */
#define umS_String_remove(self, pos, off) umS_String_put(self, NULL, pos, off)

/**
 * Gets the previous position, starting from the position passed.
 */
#define umS_String_prev(self, pos) umS_String_seek(self, pos, (-1))

/**
 * Gets the next position, starting from the position passed.
 */
#define umS_String_next(self, pos) umS_String_seek(self, pos, 1)

/**
 * Gets a pointer to the first valid character of a string.
 * It generally means the beginning of the string pointer.
 */
umIAPI char *umS_String_first(const umS_String *self);

/**
 * Gets the last character of the string.
 */
umIAPI char *umS_String_last(const umS_String *self);

/**
 * Retrieves a character position from the start of the string.
 */
umIAPI char *umS_String_index(const umS_String *self, unsigned long pos);

/**
 * Retrieves a position back or forth the position passed.
 * Negative values in @c offset returns previous positions, while positive
 * values retrieves next positions. Those positions are returned in character
 * boundaries, that is, the interface is able to return at least one character
 * from the resulting position.
 * 
 * The performance of this method depends on the character trait's
 * implementation and, maybe, on the encoding used. Seeking backwards may be an
 * inefficient operation, and may need traversing the entire string, from the
 * beginning to the current position.
 */
umIAPI char *umS_String_seek(const umS_String *self, char *pos, long offset);

/**
 * Calculates the character length of the string.
 */
umIAPI unsigned long umS_String_calclen(const umS_String *self);

/**
 * Calculates the hash code for the string. 
 */
umIAPI long umS_String_calchash(const umS_String *self);

/**
 * Concatenates two strings, and returns the result.
 * Shifts the ending null character in the concatenation.
 */
umIAPI umS_String *umS_String_cat(
	const umS_String* self,
	const umS_String* other);

/**
 * Compares two strings, based on their encodings.
 * A return value of @c 0 means that the strings are equal.
 * A return value of @c 1 means @c self is greater than @c other.
 * A return value of @c -1 means @c self is less than @c other.
 * Any other return value means that strings are not comparable (because
 * they're not in the same encoding, or because they couldn't be coerced into
 * another encoding, for example), and the user must check that.
 * This method is not safe unless both strings are in the same encoding,
 * and are well formed (in the context of their encodings).
 */
umIAPI int umS_String_coll(
	const umS_String* self,
	const umS_String* other);

umIAPI umS_String *umS_String_slice(
	const umS_String *self,
	const char *pos,
	long offset);

umIAPI umS_String *umS_String_put(
	const umS_String *self,
	const umS_String *other
	const char *pos,
	long offset);

umIAPI umS_String *umS_String_tok(
	const umS_String *self,
	const umS_String *sep,
	const char *pos,
	char **nextpos);

umIAPI umS_String *umS_String_lower(
	const umS_String *self);

umIAPI umS_String *umS_String_upper(
	const umS_String *self);

umIAPI umS_String *umS_String_swapcase(
	const umS_String *self);

umIAPI umS_String *umS_String_reverse(
	const umS_String *self);

umIAPI char *umS_String_str(
	const umS_String *self,
	const umS_String *other);

umIAPI char *umS_String_rstr(
	const umS_String *self,
	const umS_String *other);

umIAPI char *umS_String_spn(
	const umS_String *self,
	const umS_String *lst,
	char **lst_char);

/*
insert - inserts a string into an index.
remove - removes a set of characters from one index to another.
slice - retrieves a portion of the string, from one index to another.
setslice - sets a portion of the string as another string.
str - locates first ocurrence of a string
rstr - locates last ocurrence of a string
spn - locates the first ocurrence of any character from a string
tok - splits the string into smaller parts, delimited by the string passed
lower - sets all characters of a string to lowercase
upper - sets all characters of a string to uppercase
swapcase - swaps the case of characters in a string
reverse - reverses the entire string

* slice, insert and co. can do the job of those:
	at - returns a single int ("byte" character) from a specified position
	wat - retruns a single wint_t ("wide" character) from a specified position
	removeat - same as 'at', but removes the character.
	removewat - same as 'wat', but removes the character.
*/

#endif
