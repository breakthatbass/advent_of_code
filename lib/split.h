/******************************************************************************
*
*   Author: Taylor Gamache
*   Email: gamache.taylor@gmail.com
*
*   Version: 0.1.2
*
*   License: MIT 2020
*
******************************************************************************/

#ifndef __SPLIT_H__
#define __SPLIT_H__

#ifdef __cplusplus
extern "C" {
#endif

// split: split a string into an array of strings based on delimiter
char **split(char *s, const char *delim);

// print_arr: print each string in an array of strings
void print_arr(char **vec);

// arr_len: get length of an array of strings
int arr_len(char **vec);

#ifdef __cplusplus
}
#endif // extern "C"

#endif // __SPLIT_H__