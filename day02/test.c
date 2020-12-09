#include <stdio.h>

#define MAXLINE 30


int main()
{
	int low, high;
	char l;
	char pass[MAXLINE];
	char buf[MAXLINE];

	while (scanf("%d-%d %c %31s", &low, &high, &l, pass) == 4) {
		printf("low: %d high: %d l: %c pass: %s\n", low, high, l, pass);	
	}
}
