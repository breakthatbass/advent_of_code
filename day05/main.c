#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../lib/converter.h"
#include "../timing.h"

#define BUF 15
#define TKTLEN 1024

// qsort
static int cmpfunc (const void * a, const void * b) {return ( *(int*)a - *(int*)b );}

/* parse ticket, convert to binary, place binary in both row and col strings */
static void to_bin(char *ticket, char **row, char **col)
{
    *row = calloc(10, sizeof(char));
    *col = calloc(10, sizeof(char));
    if (!row || !col) {
        perror("calloc");
        exit(1);
    }

    while (*ticket) {
        switch(*ticket) {
        case 'F':
            *(*row)++ = '0';
            break;
        case 'B':
            *(*row)++ = '1';
            break;
        case 'L':
            *(*col)++ = '0';
            break;
        case 'R':
            *(*col)++ = '1';
            break;
        default:
            break;
        }
        ticket++;
    }
    *row -= 7;
    *col -= 3;
}


int find_my_ticket(int *tkts, int len)
{
    qsort(tkts, len, sizeof(int), cmpfunc);

    while (*tkts++) {
        if (*tkts == *(tkts+1)-1)
            continue;
        else return *tkts+1;
    }
    return 0; // problemz
}


int main()
{
    char buf[BUF];
    char *row = NULL;
    char *col = NULL;
    int seat, largest_seat;
    timing t;

    uint32_t row_dec, col_dec;

    int tkts[TKTLEN]; int i = 0;

    start_timing(&t);
    while (fgets(buf, BUF, stdin)) {
        
        to_bin(buf, &row, &col);

        /* convert to decimals */
        row_dec = btod(row);
        col_dec = btod(col);
        
        seat = row_dec * 8 + col_dec;
        if (seat > largest_seat) largest_seat = seat;
        tkts[i++] = seat;

        free(row);
        free(col);
    }

    int my_seat = find_my_ticket(tkts, i);
    end_timing(&t);

    assert(largest_seat == 838);
    assert(my_seat == 714);

    printf("total time: %f\n", t.ttime);

    return 0;
}
