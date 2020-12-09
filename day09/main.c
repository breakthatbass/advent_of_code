#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000
#define PREAMBLE 25

int len = 0;
unsigned long nums[MAXLEN];
unsigned long p[PREAMBLE];

void get_pre(int pos)
{
	int i;
	int start = pos-PREAMBLE;
	for (i = 0; i < PREAMBLE; i++) 
		p[i] = nums[start++];
}


int main()
{
	int i, j, k;

	i = 0;
	while (scanf("%lu", &nums[i++]) == 1) {
		len++;		
	}

	// PART !	
	int got_it = 0;
	for (i = PREAMBLE; i < len; i++) {
		get_pre(i);
		for (j = 0; j < PREAMBLE; j++) {
			for (k = 0; k < PREAMBLE; k++) {
				if (j == k) continue;  // don't add the same numbers
				if ((p[j]+p[k]) == nums[i]) got_it = 1;
			}
		}
		if (got_it == 0) printf("part1: %lu\n", nums[i]);
		got_it = 0;
	}



	return 0;
}

