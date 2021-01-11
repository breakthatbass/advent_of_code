#ifndef __CONVERTERS_H__
#define __CONVERTERS_H__

#define MAXBIN 64


// binary to decimal converter
uint64_t btod(char *bin);

// decimal to binary converter
char *dtob(uint64_t n);

// pad binary number with proper amount of zeros
char *pad_bin(char *bin);

#endif