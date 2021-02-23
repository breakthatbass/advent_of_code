#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSTRUCT 15
#define MAXBOOT 2000

struct bootcode {
	char instr[INSTRUCT];
	signed int val;
	int touched;
};
struct bootcode gameboy[MAXBOOT];

static int len = 0; // keep track of length of gameboy array
static int accumulator = 0;

// add instructions into the struct
struct bootcode *load_code(char *ins, signed int val)
{
    struct bootcode *tmp = malloc(sizeof(struct bootcode));
    
    strcpy(tmp->instr, ins);
    tmp->val = val;
    tmp->touched = 0;

    return tmp;
}

// run the instructions
void exec_boot_code(struct bootcode *code)
{
    int i = 0;

    // keep looping until we hit an instruction we've already seen
    while (code[i].touched == 0) {
        if (strcmp(code[i].instr, "acc") == 0) {
            code[i].touched = 1;
            accumulator += code[i++].val;
        } else if (strcmp(code[i].instr, "jmp") == 0) {
            code[i].touched = 1;
            i += code[i].val;
        } else code[i++].touched = 1; // got a nop instruction
    }
}


int main()
{
    char in[INSTRUCT];
    signed int n;
    int i;

    i = 0;
    while (fscanf(stdin, "%s %d", in, &n) == 2) {
        struct bootcode *bc = load_code(in, n);
        gameboy[i++] = *bc;
        free(bc);
        len++;
    }
   
    exec_boot_code(gameboy);
    printf("part 1: %d\n", accumulator);

    return 0;
}
