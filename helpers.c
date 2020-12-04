#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

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


// count_lines: get number of lines and length of each line from a file
int count_lines(char *file)
{
    FILE *fp;
	char c;
	int count = 0;
    int line = 0;

    fp = file_ptr(file);

	while ((c = getc(fp)) && c != EOF) {
		if (c == '\n')
			count++;
	}
    fclose(fp);
	return count;
}


// count_chars: get the number of characters in a file
long count_chars(char *file)
{
    FILE *fp;
    char c;
    int count = 0;

    fp = file_ptr(file);
    while ((c = getc(fp)) && c != EOF) {
        count++;
    }
    fclose(fp);
    return count;
}


// load_array: add chars from file into array
char *load_array(char *file, int length)
{
	int i;
	static char *arr;  // array to fill
	FILE *fp;
	fp = file_ptr(file);

	arr = (char*)malloc(sizeof(char) * length);
	if (arr == NULL) errmsg("memory problems\n");

	char line[MAXLINE]; // read into this line

	i = 0;
	while(fgets(line, MAXLINE, fp)) {
		// convert to int and append to nums array
		*(arr + i) = *line;
		i++;
	}
	fclose(fp);
	return arr;
}

