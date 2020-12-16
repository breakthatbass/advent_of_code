#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANGES 2
#define RULES 22
#define MAXLINE 150

long total = 0;	// variable for part 1 answer

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
	rule *r = malloc(sizeof(rule));

	char *name = malloc(sizeof(char)*40);
	strcpy(name, strtok(s, ":"));

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


void test_num(int n)
{
	int i;
	for (i = 0; i < pos; i++) {
		if ((n >= rules[i]->ranges[0].low && 
			n <= rules[i]->ranges[0].high) ||
			(n >= rules[i]->ranges[1].low && 
			n <= rules[i]->ranges[1].high)) {
				return;
			}
	}
	total += n;
}

// parse the number line string into individual numbers
void get_nums(char *s)
{
	const char *tok;
	for (tok = strtok(s, ","); tok&&*tok; tok = strtok(NULL, ",")) {
		test_num(atoi(tok));
	}
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

	line = 0;
	while (fgets(buf, MAXLINE, stdin)) {
		if (line++ < 3) continue; // move pointer ahead to numbers
		get_nums(buf);
		memset(buf, 0, MAXLINE);
	}

	printf("part 1: %ld\n", total); // 707627 too high 2352859
	return 0;
}
