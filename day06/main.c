#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 250
#define ALPHAMAX 26


void errmsg(char *msg);
FILE *file_ptr(char *file);

// for use with qsort()
int cmpfunc (const void * a, const void * b) {return ( *(char*)a - *(char*)b );}


// get answers from group
int get_answers(char *s)
{	
	int i;
	int count = 0;
	size_t len = strlen(s);

	qsort(s, len, sizeof(char), cmpfunc);

	for (i = 0; i < len; i++) {
		if (s[i] == '\n') continue;
		if (s[i] == s[i+1]) continue;
		else count++;
	}
	printf("%d\n", count);
	return count;
}


int main(int argc, char **argv)
{
	if (argc != 2) errmsg("usage: ./passport <input-file>");

	char *file = argv[1];
	// file_ptr opens file, error checks, returns ptr
	FILE *fp = file_ptr(file);

	int c;
	int i = 0;
	int total = 0;
	char buffer[MAXLINE];


	while ((c = fgetc(fp))) {
		// detect a blank line indicating we've got a group
        if (c == '\n' && buffer[i-1] == '\n') {
			total += get_answers(buffer);
			printf("%s\n", buffer);
			memset(buffer, 0, MAXLINE);
			i = 0;
		} else if (feof(fp)) {
            // we're at the end of file and can't detect '\n\n'
			total += get_answers(buffer);
			printf("%s\n", buffer);
			break;
        } else {
            buffer[i++] = (char)c;
        }
	}
	printf("total: %d\n", total);

	return 0;
}


// HELPERS...

// errmsg: print msg and exit
void errmsg(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}


// file_ptr: open a file ptr, error check, return the ptr
FILE *file_ptr(char *file)
{
    FILE *fp;

    fp = fopen(file, "r");
    if (fp == NULL) errmsg("cannot open file");

    return fp;
}
