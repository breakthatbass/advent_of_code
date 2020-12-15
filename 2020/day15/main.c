#include <stdio.h>
#include <stdlib.h>

#define SIZE 2020

long get2020(long *a, int turn)
{
    int i;
    long prev;
    while (turn < SIZE) {
        prev = a[turn-1];                  
        for (i = turn-2; i >= 0; i--) {
            if (prev == a[i]) {
                a[turn] = turn-i-1;
                break;
            }
        }
        // not sure why i'm getting massive negative numbers
        // but this statement seems to fix things
        if (i < 0) a[turn] = 0;
        turn++;
    }
    return a[SIZE-1];
}

int main()
{
    int turn = 0;
    long nums[SIZE];

    while(scanf("%ld,", &nums[i++]) > 0) {
        turn++;
    }

    printf("part 1: %ld\n", get2020(nums, turn));
        
    return 0;
}