#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 35
#define MAXLEN 323	// input is 323 lines long

int len = 0;	// variable for file length
char hill[MAXLEN][MAXLINE];


int check_spot(int x, int y)
{
	int n = y % 31;
	if (hill[x][n] == '#') {
		return 1;
	}
	return 0;
}

unsigned long ride_snowy_hill(int right, int down)
{
	int x = 0; 
	int y = 0;
	unsigned long tree_count = 0;

	while (x < len)	{
		if (check_spot(x, y)) tree_count++;
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

	printf("part 1: %lu\n", ride_snowy_hill(3, 1));
	printf("part 2: %lu\n", slopes);

	return 0;
}
