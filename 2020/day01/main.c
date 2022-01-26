#include <stdio.h>
#include <assert.h>

#include "../timing.h"

#define LEN 200


int part1(int *n)
{
    int i, j;
    for (i = 0; i < LEN; i++) {
        for (j = 0; j < LEN; j++) {
            if (i == j) continue;
            if (n[i] + n[j] == 2020) 
                return n[i]*n[j];
        }
    }
    return 0;
}


int part2(int *n)
{
    int i, j, k;
    for (i = 0; i < LEN; i++) {
        for (j = 0; j < LEN; j++) {
            for (k = 0; k < LEN; k++) {
                if (i == j && i == k) continue;
                if (n[i] + n[j] + n[k] == 2020)
                    return n[i]*n[j]*n[k];
            }
        }
    }
    return 0;
}


int main()
{

    int nums[LEN];
    int i = 0;
    timing t;

    start_timing(&t);
    while (fscanf(stdin, "%d", &nums[i++]) == 1);

	int p1 = part1(nums);
	int p2 = part2(nums);
    end_timing(&t);

	assert(p1 == 157059);
	assert(p2 == 165080960);
	
	printf("part 1: %d\n", p1);
	printf("part 2: %d\n", p2);
    printf("total time: %f\n", t.ttime);  // about 0.011

    return 0;
}
