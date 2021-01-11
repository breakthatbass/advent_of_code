#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWLEN 7
#define COLLEN 3
#define TKTLEN 1024

static int tkt_count = 0;

// qsort
int cmpfunc (const void * a, const void * b) {return ( *(int*)a - *(int*)b );}

// binary to decmimal converter
uint64_t btod(char *bin)
{
	uint64_t n = 0;	// decimal to return
	uint64_t base = 1;

	size_t len = strlen(bin)-1;

	int i;
	for (i = len; i >= 0; i--) {
		if (bin[i] == '1') n += base;
		base = base << 1;
	}
	return n;
}


// look through ticket array to find my ticket
int get_my_tkt(uint64_t *a, int len)
{
    qsort(a, len, sizeof(uint64_t), cmpfunc);

    while (*a++) {
        if (*a == *(a+1)-1)
            continue;
        else return *a+1;
    }
    return 0; // problemz
}


int main()
{
    int c;
    // array for all the tickets
    uint64_t *tkts = malloc(sizeof(uint64_t)*TKTLEN);
    char *rows = malloc(sizeof(char)*ROWLEN); // F & B chars
    char *col = malloc(sizeof(char)*COLLEN);  // L & R chars
    
    uint64_t h_pass = 0; // keep track of largest number

    while ((c = fgetc(stdin)) != EOF) {
        switch(c) {
        case '\n':
            rows -= ROWLEN;
            col -= COLLEN;
            //convert to dec
            uint64_t row_dec = btod(rows);
            uint64_t col_dec = btod(col);
            uint64_t total = row_dec * 8 + col_dec;
            *tkts++ = total; tkt_count++;
            if (total > h_pass) h_pass = total;
            break;
        case 'F':
            *rows++ = '0';
            break;
        case 'B':
            *rows++ = '1';
            break;
        case 'L':
            *col++ = '0';
            break;
        case 'R':
            *col++ = '1';
            break;
        default:
            break;
        }
    }
    // pointer back to start
    tkts -= tkt_count;
    int my_seat = get_my_tkt(tkts, tkt_count);

    printf("part 1: %llu\n", h_pass);
    printf("part 2: %d\n", my_seat);

    free(rows);
    free(col);
    free(tkts);

    return 0;
}