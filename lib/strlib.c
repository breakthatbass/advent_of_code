#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "strlib.h"


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
char *cpy_until(char *dst, char *s, const char t)
{
    int i = 0;

	 if (s == NULL) return NULL;

    while (*s != t && *s != '\0') {
        *dst++ = *s++;
        i++;
    }
    *dst = '\0';
    s -= i;
    dst -= i;

    return dst;
}


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
char *replace(char *s, const char orig, const char repl, int config)
{
    int i;

    if (config == FIRST) {
        i = 0;
        while (*s != orig && *s) {
            s++; i++;
        }
		if (*s == orig)
			*s = repl;
        s -= i;

        return s;

    } else if (config == ALL) {
        i = 0;
        while (*s) {
            if (*s == orig)
				*s = repl;
            s++;
            i++;
        }
        s -= i;

        return s;
    } 
    else return s;
}


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
char *strafter(const char *haystack, const char *needle)
{
    char *tmp;
    size_t len;

    if (haystack == NULL || needle == NULL)
        return NULL;

    if ((tmp = strstr(haystack, needle))) {
        len = strlen(needle);
        tmp += len;

        return tmp;
    }
    return NULL;
}


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

char *between_two_ferns(char *s, char *start, char *end)
{
    char *tmp, *end_tmp, *fern;
    size_t start_size, fern_size;

    if (!s) return NULL;

    if (!start || !end) return s;

    if ((tmp = strstr(s, start))) {
        start_size = strlen(start);
        tmp += start_size;
    } else {
        return NULL;
    }

    if ((end_tmp = strstr(tmp, end))) {
        fern_size = end_tmp - tmp;
    } else {
        return NULL;
    }

    fern = malloc(sizeof(char) * fern_size+1);
    if (fern == NULL) {
        fprintf(stderr, "between_two_ferns: malloc failure\n");
        exit(EXIT_FAILURE);
    }

    size_t i = 0;
    while (i < fern_size) {
        *fern++ = *tmp++;
        i++;
    }
    *fern = '\0';
    fern -= i;

    return fern;
}
