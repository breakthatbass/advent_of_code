#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct policy {
	int low;
	int high;
	char letter;
	char *pass;
}; typedef struct policy policy;


#define MAXLINE 30


// break string into tokens and set them as varibles
policy load_struct(char *line)
{
	policy tmp;
	
	tmp.low = atoi(strtok(line, "-"));
	tmp.high = atoi(strtok(NULL, " "));
	tmp.letter = *strtok(NULL, ":");
	tmp.pass = strtok(NULL, "\n\r\v\f");

	return tmp;
}

// check if password is valid
int check_pass(policy tmp)
{
	int i;
	int count = 0;
	size_t len = strlen(tmp.pass);
	
	for (i = 0; i < len; i++){
		if ((char)tmp.pass[i] == tmp.letter)
			count++;
	}
	
	if (count < tmp.low || count > tmp.high) {
		printf("ILLEGAL PASSWORD\n");
		return 0;
	}
	
	printf("VALID\n");
	return 1;
}


int main(int argc, char **argv)
{
	FILE *fp;
	char *file;
	char buffer[MAXLINE];
	int i, c;
	policy tmp;	

	int valid = 0; // keep track of valid passwords

	if (argc != 2) {
		fprintf(stderr, "usage: ./a.out <input-file>\n");
		exit(1);
	}

	file = argv[1];
	fp = fopen(file, "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file\n");
		exit(1);
	}

	// read from file and check if password is valid when end of line is reach
	i = 0;
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
			buffer[i++] = '\n'; // prevent strtok from reading into next line
			policy tmp = load_struct(buffer);
			int n = check_pass(tmp);
			valid += n;
			// flush out buffer
			memset(buffer, 0, MAXLINE);
			i = 0;
		}	
		else
			buffer[i++] = (char)c;
	}

	fclose(fp);

	printf("valid passwords: %d\n", valid);

	return 0;
}
