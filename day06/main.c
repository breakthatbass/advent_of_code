#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "../lib/array.h" // split

#define MAXCHAR 28
#define MAXLINE 1024


// store each groups answers for part 1
static char answers[MAXCHAR];
static int len = 0;


// search for c in answers, add if not present (part 1)
void find(char c)
{
	if (!isalpha(c)) return;

	if (strchr(answers, c) == NULL) 
		answers[len++] = c;
}



// find chars where all people answered yes (part 2)
int all_yes(char *buf)
{
	int total = 0;
	// split: break up string into array of strings based on delimiter
	char **s = split(buf, "\n");
	char *ref = malloc(sizeof(char) * strlen(*s)+1);
	assert(s);
	assert(ref);

	// copy over first string to use as a reference
	strcpy(ref, *s);

	// take care of the one liners
	if (*++s == NULL) {
		printf("%s -> ", *--s);
		printf("%zu\n", strlen(*s));
		return strlen(*s);
	}

	int ref_len = 0;
	while (*s) {
		while (*ref) {
			// X any char in ref that is not in other strings
			if (strchr(*s, *ref) == NULL) {
				*ref = 'X';
			}
			ref++;
			ref_len++;
		}
		s++;
	}
	// bring pointer back
	ref -= ref_len;
	// count all remaining chars in ref
	while(*ref) {
		if (*ref != 'X') {
			printf("%c", *ref);
			total++;
		}
		ref++;
	}

	if (total > 0) // don't print blanks
		printf(" -> %d\n", total);
	return total;
}



int main()
{
	int c, prev, i;
	char buf[MAXLINE];

	int part1 = 0;
	int part2 = 0;
	
	while ((c = fgetc(stdin))) {
		if (feof(stdin)) {
			// last group
			buf[i-1] = '\0'; // null terminate the string
			find(c);
			part1 += len;
			part2 += all_yes(buf);
			break;
		}
		if (c == '\n' && prev == '\n') {
			// we got us a group
			buf[i-1] = '\0'; // null terminate the string
			part1 += len;
			part2 += all_yes(buf);
			len = 0;
			i = 0;
			
			memset(answers, 0, MAXCHAR);
			memset(buf, 0, MAXLINE);
		}
		find(c);
		prev = c;
		buf[i++] = c;
	}
	printf("part 1: %d\n", part1);
	printf("part 2: %d\n", part2);  // 2903 low, 3558, 4222, 3312
	return 0;
}
