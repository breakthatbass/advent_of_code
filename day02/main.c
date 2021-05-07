#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct policy {
	int low;
	int high;
	char letter;
	char *pass;
}; typedef struct policy policy;


#define MAXLINE 50


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
	// XOR for the win
	if (tmp.pass[tmp.low] == tmp.letter ^ tmp.pass[tmp.high] == tmp.letter)
		return 1;
	return 0;
}


int main(int argc, char **argv)
{
	char buffer[MAXLINE];
	int i, c;
	policy tmp;	

	int valid_sled = 0;		// keep track of valid sled passwords
	int valid_toboggan = 0; // keep track of valid toboggan passwords

	while (fgets(buffer, MAXLINE, stdin)) {
		policy tmp = load_struct(buffer);

		// part one: sled
		int n = sled(tmp);
		valid_sled += n;

		// part two: toboggan
		int k = toboggan(tmp);
		valid_toboggan += k;

		memset(buffer, 0, MAXLINE);
	}

	assert(valid_sled == 582);
	assert(valid_toboggan == 729);

	printf("valid sled passwords: %d\n", valid_sled);
	printf("valid toboggan passwords: %d\n", valid_toboggan);

	return 0;
}
