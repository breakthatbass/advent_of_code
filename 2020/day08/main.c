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
// check, 1 if we're looking for last intrsuction
// check, 0 if we're looking for part 1
int exec_boot_code(struct bootcode *code, int check)
{
    int i = 0;
    // keep looping until we hit an instruction we've already seen
    while (1) {

		if (check && i == len) 
			// we're on the last instruction, and we've got our part 2
			return 1;
		else if ((check && i > len) || code[i].touched) 
			// we're in an infinite loop
			return 0;
		else if (!check && code[i].touched)
			// part 1: just exit if we've hit a touched instructon
			return 0;

        if (strcmp(code[i].instr, "acc") == 0) {
            code[i].touched = 1;
            accumulator += code[i++].val;
        } else if (strcmp(code[i].instr, "jmp") == 0) {
            code[i].touched = 1;
            i += code[i].val;
        } else code[i++].touched = 1; // got a nop instruction
    }
	return 0;
}


// reset everything to check loop again
void reset(void)
{
	int i;
	for (i = 0; i < len; i++)
		gameboy[i].touched = 0;
	accumulator = 0;
}


// change a jmp to nop or a nop to a jmp
void flip(char *instr)
{
	if (strcmp(instr, "jmp") == 0) {
			memset(instr, 0, INSTRUCT); // clear it
			strcpy(instr, "nop");
		}
	else if(strcmp(instr, "nop") == 0) {
		memset(instr, 0 , INSTRUCT);
		strcpy(instr, "jmp");
	} else return;
}


// flip an instruction then see if it gets stuck in an infinite loop
// keep going until we find the right instruction to flip
void find_corrupted(struct bootcode *code)
{
	// loop throuch each instruction, change it
	// then see if it makes it to the end
	int i;
	for (i = 0; i < len; i++) {
		reset(); // reset touched to 0
		// change the instruction
		flip(code[i].instr);
		// test it out
		if (exec_boot_code(code, 1) == 1)
			break;
		flip(code[i].instr); // change back
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

	exec_boot_code(gameboy, 0);
    printf("part 1: %d\n", accumulator);
   
	find_corrupted(gameboy);
	printf("part 2: %d\n", accumulator);

    return 0;
}
