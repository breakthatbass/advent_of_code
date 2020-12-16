#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANGES 2
#define RULES 22
#define MAXLINE 150

typedef struct range {
	int low;
	int high;
} range;

// struct for each field and its ranges
typedef struct rule {
	char *name;
	range ranges[RANGES];
} rule;

static int pos = 0;
rule *rules[RULES];


void get_rules(char *s)
{
	rule *r;
	// parse the string
	char *name = strtok(s, ":");
	int low1 = atoi(strtok(NULL, "-"));
	int high1 = atoi(strtok(NULL, " "));
	char *l2 = strtok(NULL, "-");
	// move the pointer ahead to the next number
	memmove(l2, l2+3, strlen(l2));
	int low2 = atoi(l2);
	int high2 = atoi(strtok(NULL, "\n"));

	// load into struct
	r->name = name;
	r->ranges[0].low = low1;
	r->ranges[0].high = high1;
	r->ranges[1].low = low2;
	r->ranges[1].high = high2;
	// then add to the array
	rules[pos++] = r;
}


int main()
{
	char buf[MAXLINE];
	int line = 0;

	while (fgets(buf, MAXLINE, stdin) && line < 20) {
		get_rules(buf);
		line++;
		memset(buf, 0, MAXLINE);
	}

	// seg fault
	printf("%s: ", rules[0]->name);

	return 0;
}
