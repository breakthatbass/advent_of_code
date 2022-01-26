
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"

/**
* reverse and itoa from page 62 and 64 of the second
* edition of K&R. it's a bit of my own variant
* but it's the same logic which I copied
* 
* in our program we convert each int to a string
* one by one so we don't use the reverse function
* in the itoa function that they do in the book
* we use it in our dtob func at the end instead
* */
 
 // reverse string s in place
 static void reverse(char *s)
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		 c = *(s+i);
		 *(s+i) = *(s+j);
		 *(s+j) = c;
     }
}

// convert an int to a string
static void itoa(int n, char *s)
{
	int i, sign;

	// record sign, make positive
	if ((sign = n) < 0) n = -n;

	i = 0;
	do {	// generate digits in reverse order
		s[i++] = n % 10 + '0'; // get next digit
	} while ((n /= 10) > 0);   // delete it

	if (sign < 0) s[i++] = '-';
	s[i] = '\0';
}


/**
* checks a binary to make sure the length
* is a multiple of 4, if it isn't
* padding the beginning with zeros until it is
**/
static char *pad_bin(char *bin)
{
	int i;
	char *rbin;  // the binary string we will return
	size_t len = strlen(bin);

	// figure out how many zeros to pad
	int p = 4 - len % 4;
	if (p == 4 || p == 0) return bin; // none nedded

	
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


/** get_value() stuff **/
#include <ctype.h>

#define HEXLEN 6

struct x {
	char c;
	int val;
};

static struct x hex_c[HEXLEN];  // key value pairs for each hex char

// get_value: get a decimal value from a single hex char
static int get_value(char c)
{
	int i, n;
	char ch;
	int p;

	for (i = 0, ch = 'A', n = 10; i < HEXLEN; ch++, i++, n++) {
		hex_c[i].c = ch;
		hex_c[i].val = n;
	}

	if (isnumber(c)) {
		sscanf(&c, "%d", &p);
		return p;
	}
	else if (c >= 'A' || c <= 'F') {
		// get val from struct
		for (i = 0; i < HEXLEN; i++) {
			if (c == hex_c[i].c) {
				return hex_c[i].val;
			}
		}
	} 
	return -1;
}


/* CONVERTER FUNCTIONS */

// btod: binary to decmimal converter
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


// dtob: decimal to binary converter
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


// btoh: binary to hex converter
char *btoh(char *bin)
{
	static const char *h = "123456789ABCDEF";

	int i, n;
	char *hex;	// string to return

	char *nbin = pad_bin(bin);
	int len = strlen(nbin);
	int hexlen = len/4; // need one hex for every 4 bins
	hexlen++;

	hex = malloc(sizeof(char)*hexlen);
	if (hex == NULL) {
		fprintf(stderr, "btoh: couldn't allocate memory\n");
		exit(EXIT_FAILURE);
	}

	char buf[5];
	for (i = 0; i < len; i+=4) {
		// copy over 4 bins from binary str
		memcpy(buf, nbin, 4);
		// make it a proper str
		buf[4] = '\0';
		// convert to decimal
		n = btod(buf) - 1;
		// add to hex str
		*hex++ = *(h+n);
		// move ahead four spots for the next conversion
		nbin += 4;
	}
	*hex = '\0';
	// move pointer back to start
	hex -= hexlen-1;
	return hex;
}


// htod: hex to dec
long htod(char *hex)
{	
	int i, n;
	long dec = 0;
	long base = 1;

	size_t len = strlen(hex)-1;

	hex += len;
	for (i = len; i >= 0; --i, --hex) {
		n = get_value(*hex);
		if (n < 0) {
			fprintf(stderr, "not a valid HEX\n");
			exit(EXIT_FAILURE);
		}
		dec += base * n;
		base *= 16;
	}
	return dec;
}
