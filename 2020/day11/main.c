#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100


int main(int argc, char **argv)
{
	int i, j, len;
	int seats[SIZE][SIZE];
	char buf[SIZE];

	i = 0; j = 0;
	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			len = i;
			j++;
			i = 0;
		}
		else seats[j][i++] = (char)c;
	}

	int k;

	for (i = 0; i < j; i++) {
		for (k = 0; k < len; k++) {
			printf("%c", seats[i][k]);
		}
		printf("\n");
	}

	return 0;
}
