#include <stdio.h>

#include "../timing.h"

#define MAXLINE 35
#define MAXLEN 323	// input is 323 lines long

static int len = 0;	// variable for file length
static char hill[MAXLEN][MAXLINE];


/*	ride the toboggan down the hill and hit some trees!
 *	...and count them while you're at it. */
unsigned long ride_snowy_hill(int right, int down)
{
	int x = 0; 
	int y = 0;
	unsigned long tree_count = 0;

	while (x < len)	{
		if (hill[x][y % 31] == '#') tree_count++;
		y+=right;
		x+=down;
	}
	return tree_count;
}


int main()
{
	int c;
	int i = 0;
	int j = 0;
	timing t;

	start_timing(&t);
	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			i++;
			j = 0;
			len++;
		}
		else hill[i][j++] = (char)c;
	}

	unsigned long slopes = 1;
	slopes *= ride_snowy_hill(1, 1);
	slopes *= ride_snowy_hill(3, 1);
	slopes *= ride_snowy_hill(5, 1);
	slopes *= ride_snowy_hill(7, 1);
	slopes *= ride_snowy_hill(1, 2);

	long p1 = ride_snowy_hill(3, 1);
	end_timing(&t);

	printf("part 1: %lu\n", p1);
	printf("part 2: %lu\n", slopes);
	printf("total time: %f\n", t.ttime);

	return 0;
}
