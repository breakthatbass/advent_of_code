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
	unsigned long invalid;

	i = 0;
	while (scanf("%lu", &nums[i++]) == 1) {
		len++;		
	}

	// PART 1	
	int got_it = 0;
	for (i = PREAMBLE; i < len; i++) {
		get_pre(i);
		for (j = 0; j < PREAMBLE; j++) {
			for (k = 0; k < PREAMBLE; k++) {
				if (j == k) continue;  // don't add the same numbers
				if ((p[j]+p[k]) == nums[i]) got_it = 1;
			}
		}
		if (got_it == 0) {
			invalid = nums[i];
			break;
		}
		got_it = 0;
	}


	// PART 2
	int pos = 0;	
	int passes = 0;
	int broke = 0;
	unsigned long total = 0;
	for (i = 0; i < len; i++) {
		for (j = i+1; j < len; j++) {
			total += nums[j];
			passes++;
			if (total == invalid && passes > 1) {
				pos = i;
				broke =1;
				break;
			} else if (total > invalid) {
				total = 0;
				passes = 0;
				break;
			}
		}
		if (broke == 1) break;
	}
	
	unsigned long low=nums[pos];
	unsigned long high=0;

	for (i = 0; i < passes; i++) {
		if (nums[pos+i] > high) high = nums[pos+i];
		if (nums[pos+i] < low) low = nums[pos+i];
	}

	printf("part 1: %lu\n", invalid);
	printf("part 2: %lu\n", low+high);

	return 0;
}

