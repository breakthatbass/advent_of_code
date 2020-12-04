#ifndef __HELPERS_H__
#define __HELPERS_H__
#endif

#include <stdio.h>

#define MAXLINE 500

void errmsg(char *msg);

FILE *file_ptr(char *file);

int count_lines(char *file);

long count_chars(char *file);

char *load_array(char *file, int length);
