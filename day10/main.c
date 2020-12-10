#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define MAX 100

int adapters[MAX];

// for use with qsort
int cmpfunc (const void * a, const void * b) 
{
	return (*(int*)a-*(int*)b);
}


// part 1
int jolts(int *a, int len)
{
	int i = 0;
	int ones = 0;
	int threes = 0;

	for (i = 0; i < len; i++) {
		if (adapters[i+1] - adapters[i] == 1) ones++;
		else if (adapters[i+1] - adapters[i] == 3) threes++;
	}

	// difference from outlet
	if (adapters[0]-0 == 1) ones++;
	else if (adapters[0] - 0 == 3) threes++;	
	// difference from device
	threes++;
	
	return ones*threes;
}


// part 2
long combos(int *a, int len)
{
	int i, j;
	static long paths[MAX];
	paths[len-1] = 1;

	for (i=len-2; i >= 0; i-- )
		for (j = i+1; j < len && adapters[j]-adapters[i] < 4; j++)
			paths[i] += paths[j];
	return paths[0];
}

int main()
{
	int i = 0;
	int len = 1;
	while (scanf("%d", &adapters[i++]) == 1) {
		len++;
	}

	qsort(adapters, len, sizeof(int), cmpfunc);
	
	int j = jolts(adapters, len);
	printf("Part 1: %d\n", j);	
	
	long c = combos(adapters, len);
	printf("Part 2: %ld\n", c);

	return 0;
}
