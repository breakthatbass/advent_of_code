#include <stdio.h>
#include <time.h>

#define LEN 200


int part1(int *n)
{
    int t, i, j;
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
    int t, i, j, k;
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

	clock_t start1, start2, start3, end1, end2, end3;
	float total1, total2, total3;
    int nums[LEN];
    int i = 0;
    while (scanf("%d", &nums[i++]) == 1);

	start3 = clock();

	start1 = clock();
	int p1 = part1(nums);
	end1 = clock();

	start2 = clock();
	int p2 = part2(nums);
	end2 = clock();

	end3 = clock();

	total1 = (float)(end1 - start1)/CLOCKS_PER_SEC;
	total2 = (float)(end2 - start2)/CLOCKS_PER_SEC;
	total3 = (float)(end3 - start3)/CLOCKS_PER_SEC;

    printf("part 1: %d --> time: %f\n", p1, total1);
    printf("part 2: %d --> time: %f\n", p2, total2);
	printf("total time: %f\n", total3);

    return 0;
}
