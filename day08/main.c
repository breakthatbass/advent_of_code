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


// add instructions into the struct
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


// run the instructions
void exec_boot_code(boot *code)
{
	int i = 0;
	while (code[i].touched == 0) {
		if (code[i].touched == 1) break;
		if (strcmp(code[i].instr, "acc") == 0) 
		{
			code[i].touched = 1;
			if (code[i].sign == '-') accumulator -= code[i++].value;
			else accumulator += code[i++].value;
		} 
		else if (strcmp(code[i].instr, "jmp") == 0) 
		{
			code[i].touched = 1;
			if (code[i].sign == '-') {
				i -= code[i].value;
			}
			else {
				i += code[i].value;
			}
		}
		else code[i++].touched = 1; // nop instruction
	}
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

	exec_boot_code(gameboy);
	printf("part1: %d\n", accumulator);
		
	return 0;
}
