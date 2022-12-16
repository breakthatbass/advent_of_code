// gcc a.c
// ./a.out < input

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUF 259 // length of input file...
static uint32_t elf_calories[BUF] = {0};
static uint32_t elf_i = 0;
static uint32_t current_elf = 0;

// qsort - this version will sort greatest to least
static int cmpfunc (const void *a, const void *b) { return ( *(int*)b - *(int*)a );}

int main(void)
{
	char buf[10] = {0};
	while (fgets(buf, sizeof(buf), stdin))
	{
		if (strcmp(buf, "\n") == 0)
		{
			elf_calories[elf_i++] = current_elf;
			current_elf = 0;
		}
		else
		{
			current_elf += atoi(buf);
		}
	}

	qsort(elf_calories, elf_i, sizeof(uint32_t), cmpfunc);

	printf("part 1: %u\n", elf_calories[0]);
	printf("part 2: %u\n", (elf_calories[0] + elf_calories[1] + elf_calories[2]));

	return 0;
}
