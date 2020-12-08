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


// break string into tokens and set them in the struct
policy load_struct(char *line)
{
	policy tmp;
		
	tmp.low = atoi(strtok(line, "-"));
	tmp.high = atoi(strtok(NULL, " "));
	tmp.letter = *strtok(NULL, ":");
	tmp.pass = strtok(NULL, "\n\r\v\f");

	return tmp;
}


// sled: check if password is valid according to sled policy
int sled(policy tmp)
{
	int i;
	int count = 0;
	size_t len = strlen(tmp.pass);
	
	for (i = 0; i < len; i++){
		if ((char)tmp.pass[i] == tmp.letter)
			count++;
	}
	
	if (count < tmp.low || count > tmp.high) {
		return 0;
	}
	return 1;
}


// toboggan: check if password is valid according to toboggan policy
int toboggan(policy tmp)
{
	// XOR - make sure only one condition is true
	if (tmp.pass[tmp.low] == tmp.letter ^ tmp.pass[tmp.high] == tmp.letter)
		return 1;

	return 0;
}


int main(int argc, char **argv)
{
	FILE *fp;
	char *file;
	char buffer[MAXLINE];
	int i, c;
	policy tmp;	

	int valid_sled = 0; // keep track of valid sled passwords
	int valid_toboggan = 0; // keep track of valid toboggan passwords

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
			
			// part one: sled policy
			int n = sled(tmp);
			valid_sled += n;

			// part two: toboggan policy
			int k = toboggan(tmp);
			valid_toboggan += k;

			// flush out buffer
			memset(buffer, 0, MAXLINE);
			i = 0;
		}	
		else
			buffer[i++] = (char)c;
	}

	fclose(fp);

	printf("valid sled passwords: %d\n", valid_sled);
	printf("valid toboggan passwords: %d\n", valid_toboggan);

	return 0;
}
