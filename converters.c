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
