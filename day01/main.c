#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 10
#define FILESIZE 300

int part1(int *a, int len)
{
	int i, j;
	int mult = 0;
	int passes = 0;

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			passes++;
			if (*(a+i) + *(a+j) == 2020) {
				mult = *(a+i) * *(a+j);
				printf("part1 passes: %d\n", passes);
				return mult;
			}
		}
	}
	return mult;
}


int part2(int *a, int len)
{
	int i, j, k;
	int mult = 0;
	int passes = 0;

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			for (k = 0; k < len; k++) {
				passes++;
				if (*(a+i) + *(a+j) + *(a+k) == 2020) {
					mult = *(a+i) * *(a+j) * *(a+k);
					printf("part2 passes: %d\n", passes);
					return mult;
				}
			}
			
		}
	}
	return mult;
}

int main()
{
	int len = 0;
	int nums[FILESIZE];

	int i = 0;
	while (scanf("%d", &nums[i++]) == 1) {
		len++;
	}


	int p1 = part1(nums, len);
	int p2 = part2(nums, len);
	printf("part 1: %d\n", p1);
	printf("part 2: %d\n", p2);

	return 0;
}
