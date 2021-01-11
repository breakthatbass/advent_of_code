#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "converters.h"

// binary to decmimal converter
uint64_t btod(char *bin)
{
	uint64_t n = 0;	// decimal to return
	uint64_t base = 1;

	size_t len = strlen(bin)-1;

	int i;
	for (i = len; i >= 0; i--) {
		if (bin[i] == '1') n += base;
		base = base << 1;
	}
	return n;
}


// decimal to binary converter
char *dtob(uint64_t n)
{
	static char bin[MAXBIN];
	int i;

	for (i = 0; n > 0; i++) {
		// convert to string and plug into b array
		itoa((n % 2), &bin[i]);
		n = n >> 1;
	}
	reverse(bin);
	return bin;
}


char *pad_bin(char *bin)
{
	int i;
	char *rbin;  // the binary string we will return
	size_t len = strlen(bin);

    if (len == 32) return bin;
	// figure out how many zeros to pad
	//int p = 4 - len % 4;
	//if (p == 4 || p == 0) return bin; // none nedded

    int p = 33 - len-1;
	
	int plen = p+len+1;
	rbin = malloc(sizeof(char)*plen);
	if (rbin == NULL) {
		fprintf(stderr, "pad_hex: memory problems\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < p; ++i)
		*rbin++ = '0';  // do the padding
	while (*bin != '\0')
		*rbin++ = *bin++;
	*rbin = '\0';

	// get pointer back to the beginning
	rbin -= plen - 1;
	return rbin;
}
