/******************************************************************************
*
*   Author: Taylor Gamache
*   Email: gamache.taylor@gmail.com
*
*   Version: 0.0.2
*
*   License: MIT 2020
*
******************************************************************************/

#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAXBIN 64

// btod: binary to decmimal converter
uint64_t btod(char *bin);

// dtob: decimal to binary converter
char *dtob(uint64_t n);

// btoh: binary to hex converter
char *btoh(char *bin);

// htod: hex to dec
long htod(char *hex);

#ifdef __cplusplus
}
#endif // extern "C"

#endif // __CONVERTER_H__
