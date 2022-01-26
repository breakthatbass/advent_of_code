#ifndef STRLIB_H__
#define STRLIB_H__


/* *
 *	cpy_until:
 *
 * DESCRIPTION:
 *		Copy string s into string dst until char t is encountered. If char t is never
 *		encoutnered, the etirety of string s gets copied.
 *
 *	RETURN VALUE:
 *		Returns a pointer to the start of string dst. If s is NULL, NULL is
 *		returned.
 * */
char *cpy_until(char *dst, char *s, const char t);


/* *
 *	replace:
 * 
 *	DESCRIPTION:
 *		replace char orig with char repl in string s. Config can be FIRST or ALL.
 *		FIRST: replace the first instance of char orig and char repl.
 *		ALL: replace all instances of char orig with char repl.
 *
 *	RETURN VALUE:
 *		Returns a pointer to string s. If something other than FIRST or ALL is
 *		supplied for config, it simply returns a pointer to s without doing
 *		anything. Also, if char orig is not found in s, it also returns a
 *		pointer to s.
 *
 *      enum config { FIRST = 1, ALL = 2 };
 * */
enum config { FIRST = 1, ALL = 2 };

char *replace(char *s, const char orig, const char repl, int config);


/* *
 *	strafter:
 *
 * DESCRIPTION:
 *		strafter searches string haystack for substring needle. if found, it returns
 *		a pointer to the string haystack after needle. similar to strstr.
 *
 *	RETURN VALUE:
 *		returns a pointer to location in haystack after substring needle. If
 *		needle is not in haystack, it returns NULL.
 *
 * */
char *strafter(const char *haystack, const char *needle);



/* *
 *	between_two_ferns(char *s, char *start, char *end)
 *
 * DESCRIPTION:
 *		search string s for strat, if it exists, copy all characters until
 *      end is encounted.
 *
 *	RETURN VALUE:
 *		returns a pointer to the string between start and end.
 *      if only one of start or end exist, or neither exist, return s.
 *      user must free.
 *
 * */
char *between_two_ferns(char *s, char *start, char *end);


#endif
