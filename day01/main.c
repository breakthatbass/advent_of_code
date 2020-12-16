#include <stdio.h>

#define MAXLINE 10
#define LEN 200


int part1(int *n)
{
    int t, i, j;
    for (i = 0; i < LEN; i++) {
        for (j = 0; j < LEN; j++) {
            if (i == j) continue;
            if (n[i] + n[j] == 2020) 
                t = n[i]*n[j];
        }
    }
    return t;
}


int part2(int *n)
{
    int t, i, j, k;
    for (i = 0; i < LEN; i++) {
        for (j = 0; j < LEN; j++) {
            for (k = 0; k < LEN; k++) {
                if (i == j && i == k) continue;
                if (n[i] + n[j] + n[k] == 2020)
                    t = n[i]*n[j]*n[k];
            }
        }
    }
    return t;
}


int main()
{
    int nums[LEN];
    int i = 0;
    while (scanf("%d", &nums[i++]) == 1);

    printf("part 1: %d\n", part1(nums));
    printf("part 2: %d\n", part2(nums));

    return 0;
}