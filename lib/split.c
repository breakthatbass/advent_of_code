#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "split.h"

static char *trim(char *str)
{
  char *end;
  
  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  if (*end != ' ') return str;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

// split: take a string and break it up into an array of strings based on delim
char **split(char *s, const char *delim)
{
    char **split_s;
    char *token, *tmp;
    size_t length;
    int i;

    length = strlen(s);

	tmp = malloc(sizeof(char)*length+1);
	if (tmp == NULL) {
		fprintf(stderr, "split: could not allocate memory\n");
		exit(EXIT_FAILURE);
	}
	strcpy(tmp, s);
	tmp[length] = '\0';

    split_s = calloc(length*2, sizeof(char*));
    if (split_s == NULL) {
        fprintf(stderr, "split: could not allocate memory\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    token = strtok(tmp, delim);
    while (token != NULL) {
		split_s[i] = trim(token);
        token = strtok(NULL, delim);
        i++;
    }
	if (i > 0)split_s[i] = NULL;
    return split_s;
}


// print_arr: each string in an array of strings
void print_arr(char **vec)
{
    int len = 0;
    while (*vec) {
        printf("%s\n", *vec);
        len++;
        vec++;
    }
    vec -= len;
}


// arr_len: get length of an array of strings
int len(char **vec)
{
    int l = 0;
    while(*vec) {
        vec++;
        l++;
    }
    vec -= l;
    return l;
}

