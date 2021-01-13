#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCHAR 28


// store each groups answers
static char answers[MAXCHAR];
static int len = 0;


// search for c in answers, add if not present
void find(char c)
{
	if (!isalpha(c)) return;

	if (strchr(answers, c) == NULL) 
		answers[len++] = c;
}


int main(int argc, char **argv)
{
	int c, prev;
	int total = 0;
	
	while ((c = fgetc(stdin))) {
		if (feof(stdin)) {
			find(c);
			total += len;
			break;
		}
		if (c == '\n' && prev == '\n') {
			total += len;
			len = 0;
			memset(answers, 0, MAXCHAR);
		}
		find(c);
		prev = c;
	}
	printf("part 1: %d\n", total);
	return 0;
}
