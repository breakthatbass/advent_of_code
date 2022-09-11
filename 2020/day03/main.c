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

#define MAXLINE 35
#define MAXLEN 323	// input is 323 lines long

static uint16_t len = 0;	// variable for file length
static char hill[MAXLEN][MAXLINE];


/*	ride the toboggan down the hill and hit some trees!
 *	...and count them while you're at it. */
uint8_t ride_snowy_hill(uint8_t right, uint8_t down)
{
	uint8_t x = 0; 
	uint8_t y = 0;
	uint8_t tree_count = 0;

	while (x < len)	{
		if (hill[x][y % 31] == '#') tree_count++;
		y += right;
		x += down;
	}
	return tree_count;
}


int main()
{
	int c;
	uint16_t i = 0;
	uint16_t j = 0;

	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			i++;
			j = 0;
			len++;
		}
		else hill[i][j++] = (char)c;
	}

	uint32_t slopes = 1;
	slopes *= ride_snowy_hill(1, 1);
	slopes *= ride_snowy_hill(3, 1);
	slopes *= ride_snowy_hill(5, 1);
	slopes *= ride_snowy_hill(7, 1);
	slopes *= ride_snowy_hill(1, 2);

	long p1 = ride_snowy_hill(3, 1);

	printf("part 1: %lu\n", p1);
	printf("part 2: %u\n", slopes);

	return 0;
}
