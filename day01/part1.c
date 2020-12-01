#include <stdio.h>
#include <stdlib.h>

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


// twenty20: find the first two numbers in arr that add up to 2020
int twenty20(int *arr, int len)
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



int main(int argc, char **argv)
{
	FILE *fp;
	int *nums;
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
	nums = load_array(file, len);
	int total  = twenty20(nums, len);

	printf("The answer is...%d\n", total);
	
	free(nums);
	fclose(fp);

	return 0;
}
