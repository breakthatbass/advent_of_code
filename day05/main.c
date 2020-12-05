#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 20
#define ROW 8
#define COL 4


// for use with qsort()
int cmpfunc (const void * a, const void * b) {return ( *(int*)a - *(int*)b );}

// count_lines: get number of lines and length of each line from a file
int count_lines(char *file)
{
    FILE *fp;
	char c;
	int count = 0;
    int line = 0;

    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "cannot open file\n");
        exit(1);
    }

	while ((c = getc(fp)) && c != EOF) {
		if (c == '\n')
			count++;
	}
    fclose(fp);
	return count;
}

char *get_row(char *tkt)
{
    char *row = (char*)malloc(sizeof(char)*ROW);
    if (row == NULL) {
        fprintf(stderr, "mem problems\n");
        exit(1);
    }
    strncpy(row, tkt, 7);
    return row;
}


// compute row into the number
int comrow(char *s)
{
    int b_up = 127;  
    int b_low = 0;    
    int i;
    size_t len = strlen(s);
    for (i = 0; i < len; i++){
        if (s[i] == 'F') b_up = (b_up + b_low)/2;   
        else b_low = (b_up + b_low+1)/2;
    }
    return b_low;
}


// compute column into the number
int comcol(char *s)
{
    int c_up = 7;
    int c_low = 0;
    int i;
    size_t len = strlen(s);
    for (i = 0; i < len; i++) {
        if (s[i] == 'L') c_up = (c_up+c_low)/2;
        else c_low = (c_up+c_low+1)/2;
    }
    return c_low;
}


// get column chars
char *get_col(char *tkt)
{
    char *col = (char*)malloc(sizeof(char)*COL);
    if (col == NULL) {
        fprintf(stderr, "mem problems\n");
        exit(1);
    }
    col = strtok(&tkt[7], "\n");
    return col;
}

// part 2, sort array of tickets, get the missing one
int get_tkt(int *a, int len)
{
    int i;
    qsort(a, len, sizeof(int), cmpfunc);
    for (i = 0; i < len; i++) {
        if (a[i] == (a[i+1]-1))
            continue;
        else return a[i]+1;
    }
    return 0; // problemz
}


// return the ID of a ticket
int get_id(int row, int col)
{
    return row * 8 + col;
}


int main(int argc, char **argv)
{
    char buffer[MAXLINE];
    
    if (argc != 2) {
		fprintf(stderr, "usage: ./a.out <input-file>\n");
		exit(1);
	}

	char *file = argv[1];

    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "cannot open file\n");
        exit(1);
    }

    int file_len = count_lines(file);
    int *ids = (int*)malloc(sizeof(int)*file_len);

    int big_id = 0;
    int c;
    int n;
    int i = 0;
    int j = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            
            // get chars for col and rows, then get their numbers
            char *row = get_row(buffer);
            char *col = get_col(buffer);
            int x = comrow(row);
            int y = comcol(col);
            
            // get id
            n = get_id(x, y);
            // if current ID is larger, replace it
            if (n > big_id) big_id = n;
            ids[j++] = n; // add id to array

            // flush out buffer
			memset(buffer, 0, MAXLINE);
			i = 0;
        } else buffer[i++] = (char)c;
    }
    fclose(fp);

    printf("Biggest ID: %d\n", big_id);
    int my_seat = get_tkt(ids, file_len);
    printf("my seat: %d\n", my_seat);
    

    return 0;
}