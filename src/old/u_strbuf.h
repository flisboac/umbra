/**
 * @file u_string.h
 * 
 * An utility module used by other modules that needs to work with
 * string buffers.
 * Some basic functionality is implemented for strings, like
 * concatenation, comparison and the like. In general, it's not
 * possible to use two strings with different encodings in the same
 * operation; for that, you need to convert them into the same
 * encoding.
 */

#ifndef U_STRBUF_H_
#define U_STRBUF_H_


/**
 * A string capable of growing or shrinking automatically.
 * An important note to take for a string buffer is that it can be used as 
 * a normal string, and even be passed to the string interface functions with
 * no problem.
 * Most operations act on the string buffer itself, altering its state
 * constantly. Because of that, the length and hash values must be calculated
 * just after any operation. This won't be done automatically, unless
 * absolutely needed. Note, as well, that just as is the case with normal
 * strings, if the state of the buffer changes, any positional pointers become
 * automatically invalid, because the implementation is free to reallocate
 * memory as needed.
 */
typedef struct umS_Buffer {

	/**
	 * The string portion. 
	 */
	umS_String str;

	/**
	 * If true, the buffer cannot grow or shrink automatically.
	 * This property effectively makes the string buffer act as a normal
	 * string.
	 */
	char noresize;

	/** 
	 * The total (memory) size of the string, in bytes.
	 */
	size_t cap;

} umS_Buffer;


umIAPI umS_Buffer *umS_Buffer_fromcstr(
	const char *cstr);
umIAPI umS_Buffer *umS_Buffer_fromwstr(
	const wchar_t *wstr);
umIAPI umS_Buffer *umS_Buffer_fromstring(
	const umS_String *str);
umIAPI umS_Buffer *umS_Buffer_from(
	const umS_Buffer *buf);
umIAPI umS_Buffer *umS_Buffer_new(
	size_t cap);
umIAPI void umS_Buffer_dispose(
	umS_Buffer *self);

umIAPI int umS_Buffer_cat(
	umS_Buffer *self,
	const umS_String *str);
umIAPI int umS_Buffer_put(
	umS_Buffer *self,
	const umS_String *other
	const char *pos,
	long offset);
umIAPI int umS_Buffer_tok(
	umS_Buffer *self,
	const umS_String *sep,
	const char *pos,
	char **nextpos);
umIAPI int umS_Buffer_lower(
	umS_Buffer *self);
umIAPI int umS_Buffer_upper(
	umS_Buffer *self);
umIAPI int umS_Buffer_swapcase(
	umS_Buffer *self);
umIAPI int umS_Buffer_reverse(
	umS_Buffer *self);
umIAPI int umS_Buffer_clear(
	umS_Buffer *self);
umIAPI int umS_Buffer_resize(
	umS_Buffer *self,
	size_t cap);
umIAPI int umS_Buffer_assertsz(
	umS_Buffer *self,
	unsigned long size);

/*

fromcstr
fromwstr
fromstring
from
new
dispose
tostring

ctype (provided by umS_String)
ctypeat (provided by umS_String)

char (provided by umS_String)
charat (provided by umS_String)
insert (provided by umS_String)
remove (provided by umS_String)
prev (provided by umS_String)
next (provided by umS_String)

first (provided by umS_String)
last (provided by umS_String)
index (provided by umS_String)
seek (provided by umS_String)
calclen (provided by umS_String)
calchash (provided by umS_String)
cat
coll (provided by umS_String)
slice (provided by umS_String)
put
tok
lower
upper
swapcase
revert
str (provided by umS_String)
rstr (provided by umS_String)
spn (provided by umS_String)

clear
resize
assertsz

*/

#endif
