#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXDIGIT 10


// count_lines: get number of lines from a file
int count_lines(FILE *fp)
{
	char c;
	int count = 0;

	while ((c = getc(fp)) && c != EOF) {
		if (c == '\n')
			count++;
	}
	return count;
}


// load_array: add numbers from file into array
int *load_array(char *file, int file_length)
{
	int i;
	static int *nums;  // array to fill
	FILE *fp;
	fp = fopen(file, "r");

	nums = (int*)malloc(sizeof(int) * file_length);
	if (nums == NULL) {
		fprintf(stderr, "memory allocation failure...\n");
		exit(1);
	}

	char line[MAXDIGIT]; // read into this line

	i = 0;
	while(fgets(line, MAXDIGIT, fp)) {
		// convert to int and append to nums array
		*(nums + i) = atoi(line);
		i++;
	}
	fclose(fp);
	return nums;
}


// find the first two numbers in arr that add up to 2020
int part1(int *arr, int len)
{
	int i, j;
	int mult = 0;

	for (i = 0; i < len; i++) {
		for ( j = 0; j < len; j++) {
			if (*(arr+i) + *(arr+j) == 2020) {
				mult = *(arr+i) * *(arr+j);
				return mult;
			}
		} 
	}
	return mult;
}


// find the first THREE numbers in arr that add up to 2020
int part2(int *arr, int len)
{
	int i, j, k;
	int mult = 0;

	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			for (k = 0; k < len; k++) {
				if (*(arr+i) + *(arr+j) + *(arr+k) == 2020) {
					mult = *(arr+i) * *(arr+j) * *(arr+k);
					return mult;
				}
			} 
		}
	}
	return mult;
}



int main(int argc, char **argv)
{
	FILE *fp;
	char *file;

	if (argc != 2) {
		fprintf(stderr, "usage: ./a.out <file>\n");
		exit(1);
	}

	file = argv[1];

	fp = fopen(file, "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file\n");
		exit(1);
	}

	int len = count_lines(fp);
	int *nums = load_array(file, len);
	int part1_total  = part1(nums, len);
	int part2_total = part2(nums, len);

	// tests
	if (strcmp(file, "input_test") == 0) {
		assert(part1_total == 514579);
		assert(part2_total == 241861950);
	}

	printf("The answer is...\n\tpart 1: %d\n\tpart 2: %d\n", part1_total, part2_total);
	
	free(nums);
	fclose(fp);

	return 0;
}

