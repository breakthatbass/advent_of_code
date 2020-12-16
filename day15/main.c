#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P1 2020
#define P2 30000000


int main()
{
    int turn = 0;
    int prev;
    int i = 0;
    static unsigned int seen[P2];
    
    while(scanf("%d,", &i) > 0) {
        seen[prev] = turn;
        prev = i;
        turn++;
    }
    prev = 
    while (turn < P2) {
        prev = a[turn-1];  
        /*                
        for (i = turn-2; i >= 0; i--) {
            if (prev == a[i]) {
                a[turn] = turn-i-1;
                break;
            }
        }
        */
        // not sure why i'm getting massive negative numbers
        // but this statement seems to fix things
        if (i < 0) a[turn] = 0;
        turn++;
    }
    printf("part 2: %d\n", i);        
    return 0;
}