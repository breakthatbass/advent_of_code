#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBOOT 2000
#define MAXLINE 30

typedef struct bootcode {
	char *instr;
	char sign;
	int value;
	int touched;
} boot;

boot gameboy[MAXBOOT];

int len = 0;
int accumulator = 0;

boot *load_code(char *instruction, char *value)
{
	boot *tmp = malloc(sizeof(boot));
	tmp->instr = malloc(sizeof(char)*4);

	strcpy(tmp->instr, instruction);
	tmp->sign = value[0];
	tmp->value = atoi(value+1);
	tmp->touched = 0;

	return tmp;
}

int main()
{
	char in[MAXLINE];
	char v[MAXLINE];

	int c;
	int i = 0;
	while (scanf("%s %s", in, v) == 2) {
		boot *bc = load_code(in, v);	
		gameboy[i++] = *bc;
		len++;
	}

	i = 0;
	while (gameboy[i].touched == 0) {
		if (gameboy[i].touched == 1) break;
		if (strcmp(gameboy[i].instr, "acc") == 0) 
		{
			gameboy[i].touched = 1;
			if (gameboy[i].sign == '-') accumulator -= gameboy[i++].value;
			else accumulator += gameboy[i++].value;
		} 
		else if (strcmp(gameboy[i].instr, "jmp") == 0) 
		{
			gameboy[i].touched = 1;
			if (gameboy[i].sign == '-') {
				i -= gameboy[i].value;
			}
			else {
				i += gameboy[i].value;
			}
		}
		else gameboy[i++].touched = 1; // nop instruction
	}
	printf("part1: %d\n", accumulator);
		
	return 0;
}
