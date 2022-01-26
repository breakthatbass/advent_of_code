#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P1 2020
#define P2 30000000

int main()
{
	static int numbers[P2];
	int n;
	int turns = 0;
	int prev = 0;

	while (fscanf(stdin, "%d,", &n) == 1) {
		numbers[prev] = turns;
		prev = n;
		turns++;
	}

	int i;
	while (turns < P2) {
		if (numbers[prev])
			n = turns-numbers[prev];
		else n = 0;
		numbers[prev] = turns;
		if (turns == P1-1) printf("part 1: %d\n", n);
		prev = n;
		turns++;
	}
	printf("part 2: %d\n", n);
	return 0;
}
