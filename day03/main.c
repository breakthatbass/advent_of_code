#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

// errmsg: print msg and exit
void errmsg(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}


// file_ptr: open a file ptr, error check, return the ptr
FILE *file_ptr(char *file)
{
    FILE *fp;

    fp = fopen(file, "r");
    if (fp == NULL) errmsg("cannot open file");

    return fp;
}


// count_lines: get number of lines and length of each line from a file
int count_lines(char *file)
{
    FILE *fp;
	char c;
	int count = 0;
    int line = 0;

    fp = file_ptr(file);

	while ((c = getc(fp)) && c != EOF) {
		if (c == '\n')
			count++;
	}
    fclose(fp);
	return count;
}


// snowy_hill: create multi-dimensional array based on input file
int **init_arr(int file_len)
{
    int **hill;
    int i;
    
    hill = malloc(sizeof(int*)*file_len);
    if (hill == NULL) errmsg("malloc failed");

    for (i = 0; i < file_len; i++) {
        hill[i] = calloc(file_len*file_len, sizeof(int) * file_len);
            if (hill[i] == NULL) errmsg("calloc failed");
    }
    return hill;
}


// init_snowy_hill: load file into array repeating lines until full
void init_snowy_hill(int **arr, char *file, int file_len)
{
    char buffer[MAXLINE];

    FILE *fp = file_ptr(file);

    int c;
    int i = 0;
    int j = 0;
    int k = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            for (k = 0; k < (file_len*file_len); k++) {
                // at end of file line, repeat that line
                if (buffer[i] == 0) i = 0;
                arr[j][k] = buffer[i++];
            }
            // clear out buffer
            memset(buffer, 0, MAXLINE);
			i = 0;
            j++;
        } else buffer[i++] = (char)c;
    }

    fclose(fp);
}


// ride_snowy_hill: move through array according to right & down params
unsigned long ride_snowy_hill(int **arr, int file_len, int right, int down)
{
    int x = 0;
    int y = 0;
    unsigned long tree_count = 0;

    for (x = 0; x < file_len; x+=down) {
        if (arr[x][y] == '#') tree_count++;
        y+=right;
    }
    return tree_count;
}


int main(int argc, char **argv)
{
	if (argc != 2) errmsg("usage: toboggan <input-file>");

	char *file = argv[1];
    
    // get the amount of lines in file
    int file_len = count_lines(file);

    // allocate memory for multi-dimensional array
    int **hill = init_arr(file_len);
    
    // load array with data from input file
    init_snowy_hill(hill, file, file_len);

    // ride the toboggan!!
    unsigned long slopes = 1;
    slopes *= ride_snowy_hill(hill, file_len, 1, 1);
    slopes *= ride_snowy_hill(hill, file_len, 3, 1);
    slopes *= ride_snowy_hill(hill, file_len, 5, 1);
    slopes *= ride_snowy_hill(hill, file_len, 7, 1);
    slopes *= ride_snowy_hill(hill, file_len, 1, 2);
    
    printf("part 1: %lu\n", ride_snowy_hill(hill, file_len, 3, 1));
    printf("part 2: %lu\n", slopes);

    return 0;
}
