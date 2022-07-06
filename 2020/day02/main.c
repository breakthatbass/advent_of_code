/**
 * day 02 2020
 * https://adventofcode.com/2020/day/2
 *
 * compile:
 *    debug:   gcc main.c -o main -g -fsanitize=address -Wall
 *    release: gcc main.c -o main -O2
 * 
 * run:        ./main < input
 **/
#include <stdio.h>
#include <stdint.h>

#define LINE 50

uint8_t sled(uint32_t min, uint32_t max, char c, char *pass)
{
    uint8_t count = 0;
    while (*pass) {
        if (*pass == c) count++;
        pass++;
    }
    if (count >= min && count <= max)
        return 1;
    return 0;
}

uint8_t toboggan(uint32_t min, uint32_t max, char c, char *pass)
{
    if (pass[min-1] == c ^ pass[max-1] == c)
    {
        return 1;
    }
    return 0;
}

int main()
{
    uint32_t min, max;
    char c;
    char pass[LINE] = {0};

    uint16_t valid_sled = 0;
    uint16_t valid_toboggan = 0;

    while (fscanf(stdin, "%d-%d %c: %s", &min, &max, &c, pass) == 4) {
        valid_sled += sled(min, max, c, pass);
        valid_toboggan += toboggan(min, max, c, pass);
    }

	printf("valid sled passwords: %d\n", valid_sled);
	printf("valid toboggan passwords: %d\n", valid_toboggan);

    return 0;
}
