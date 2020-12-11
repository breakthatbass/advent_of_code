#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 120

char seats[SIZE][SIZE];
char next[SIZE][SIZE];
int width = 0; int height = 0;

int look(int j, int i)
{
	int count = 0;
	if (i > 0 && j > 0 && seats[i-1][j-1] == '#') count++;
	if (i > 0 && seats[i-1][j] == '#') count++;
	if (i > 0 && j < width && seats[i-1][j+1] == '#') count++;
	if (j > 0 && seats[i][j-1] == '#') count++;
	if (j < width && seats[i][j+1] == '#') count++;
	if (i < height && j > 0 && seats[i+1][j-1] == '#') count++;
	if (i < height && seats[i+1][j] == '#') count++;
	if (i < height && j < width && seats[i+1][j+1] == '#') count++;

	return count;
}

int visualize()
{
	int i, j;
	while (1) {
		memcpy(next, seats, sizeof(char)*SIZE*SIZE);
		int neighbors;
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				neighbors = look(j,i);
				if (neighbors == 0 && seats[i][j] == 'L') next[i][j] = '#';
				else if (neighbors >= 4 && seats[i][j] == '#') next[i][j] = 'L';
			}
		}
		if (memcmp(seats, next, sizeof(char)*SIZE*SIZE) == 0) break;
		memcpy(seats, next, sizeof(char)*SIZE*SIZE);
	}

	// count up all occupied seats
	int count = 0;
	for (i = 0; i < height; i++) 
		for (j = 0; j < width; j++)
			if (seats[i][j] == '#') count++;
	return count;
}


int main(int argc, char **argv)
{
	int i, j, c;

	i = 0;  //width = 0; height = 0;
	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			width = i;
			height++;
			i = 0;
		}
		else seats[height][i++] = c;
	}

	int taken = visualize();	
	printf("part 1: %d seats taken\n", taken);
	return 0;
}
