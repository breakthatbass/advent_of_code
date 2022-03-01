#include <stdio.h>
#include <stdint.h>
//#include <stdlib.h>

#define BUF 15
#define TKTLEN 1024

#define ROWNIB(b) (((b) >> 3) & 0x7F)	// get the upper 7 bits
#define COLNIB(b) ((b) & 0x7)			// get the lower 3 bits

// qsort
static int cmpfunc (const void * a, const void * b) {return ( *(int*)a - *(int*)b );}

// convert a string of binary chars to an unsigned int
uint32_t to_bin(char *tkt)
{
	uint32_t n = 0;

	while (*tkt != '\n') {
		n = n << 1 | (*tkt == 'B') | (*tkt == 'R');
		tkt++;
	}
	return n;
}

int find_my_ticket(uint32_t *tkts, uint32_t len)
{
    qsort(tkts, len, sizeof(int), cmpfunc);

    while (*tkts++) {
        if (*tkts == *(tkts+1) - 1)
            continue;
        else return *tkts + 1;
    }
    return 0; // problemz
}

int main(void)
{
	char buf[BUF] = {0};
	uint32_t row, col, seat, largest_seat;
	uint32_t tkts[TKTLEN]; uint32_t i = 0;

	largest_seat = 0;

	while (fgets(buf, BUF, stdin)) {
		
		seat = to_bin(buf);
		row = ROWNIB(seat);
		col = COLNIB(seat);

		seat = row * 8 + col;
		if (seat > largest_seat) largest_seat = seat;
		
		tkts[i++] = seat;
	}

	uint32_t my_seat = find_my_ticket(tkts, i);

	printf("largest seat: %d\n", largest_seat);
	printf("my seat: %d\n", my_seat);


	return 0;
}
