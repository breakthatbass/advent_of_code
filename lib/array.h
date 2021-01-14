#ifndef __ARRAY_H__
#define __ARRAY_H__

/*
 split a string into an array of strings based on delimiter
 split has to be freed when no longer needed otherwise malloced
 memory will leak
 */
char **split(char *s, const char *delim);

// print each string in an array of strings
void print_vec(char **vec);

#endif
