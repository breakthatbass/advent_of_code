#include <stdio.h>

#define P1 2020
#define P2 30000000

long get_last(long *a, int turn, long lim)
{
    int i;
    long prev;
    while (turn < lim) {
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
    return a[lim-1];
}

int main()
{
    int turn = 0;
    int i = 0;
    static long nums[P2];
    
    while(scanf("%ld,", &nums[i++]) > 0) {
        turn++;
    }

    printf("part 1: %ld\n", get_last(nums, turn, P1));
    printf("part 2: %ld\n", get_last(nums, turn, P2));
        
    return 0;
}