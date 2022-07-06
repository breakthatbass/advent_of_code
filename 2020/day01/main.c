/**
 * day 01 2020
 * https://adventofcode.com/2020/day/1
 *
 * compile:
 *    debug:   gcc main.c -o main -g -fsanitize=address -Wall
 *    release: gcc main.c -o main -O2
 * 
 * run:         ./main < input
 **/
#include <stdio.h>
#include <stdint.h>

#define LEN 200

uint32_t part1(uint16_t *n)
{
    uint8_t i, j;
    for (i = 0; i < LEN; i++) {
        for (j = 0; j < LEN; j++) {
            if (i == j) continue;
            if (n[i] + n[j] == 2020) 
                return n[i]*n[j];
        }
    }
    return 0;
}


uint32_t part2(uint16_t *n)
{
    uint8_t i, j, k;
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


int main(void)
{

    uint16_t nums[LEN] = {0};
    uint8_t i = 0;

    while (fscanf(stdin, "%hd", &nums[i++]) == 1);

	uint32_t p1 = part1(nums);
	uint32_t p2 = part2(nums);

    printf("part 1: %u\n", p1);
    printf("part 2: %u\n", p2);

    return 0;
}
