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
	int position;
	range ranges[RANGES];
} rule;

static int pos = 0;
rule *rules[RULES];

static int t_count = 0;
#define TICKETS 300
#define TKT		200
char tickets[TICKETS][TKT]; // to hold valid tickets


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


int test_num(int n)
{
	int i;
	for (i = 0; i < pos; i++) {
		if ((n >= rules[i]->ranges[0].low && 
			n <= rules[i]->ranges[0].high) ||
			(n >= rules[i]->ranges[1].low && 
			n <= rules[i]->ranges[1].high)) {
				return 0;
		}	
	}
	return 1;
}

// parse the number line string into individual numbers
void get_nums(char *s)
{
	//printf("get_nums: %s\n", s);
	char tmp[MAXLINE];
	strcpy(tmp, s);

	int t = 0; // keep track of crap tickets
	int n;
	const char *tok;
	for (tok = strtok(s, ","); tok && *tok; tok = strtok(NULL, ",")) {
		n = atoi(tok);
		if (test_num(n) == 1) {  // junk value, add to total
			total+=n;
			t++;
		}
	}
	// a ticket to keep for part 2
	if (t == 0) strcpy(tickets[t_count++], tmp);
}

// graph to use to keep track of rules and good tickets
int check_rules[190][20];

// test each number, if it passes test, add 1 to graph, other wise zero
void check_good_tkts(char *s, int p)
{
	//printf("%d\n", p);
	int n;
	int i;
	const char *tok;
	for (tok = strtok(s, ","); tok && *tok; tok = strtok(NULL, ",")) {
		n = atoi(tok);
		for (i = 0; i < pos; i++) {
			if ((n >= rules[i]->ranges[0].low && 
				n <= rules[i]->ranges[0].high) ||
				(n >= rules[i]->ranges[1].low && 
				n <= rules[i]->ranges[1].high)) {
					check_rules[p][i] = 1; // good!
			} else check_rules[p][i] = 0; // doesn't pass	
		}
	}
}


int main()
{
	char buf[MAXLINE];
	int line = 0;
	char my_ticket[MAXLINE];

	while (fgets(buf, MAXLINE, stdin) && line < 20) {
		get_rules(buf);
		line++;
		memset(buf, 0, MAXLINE);
	}

	line = 0;
	while (fgets(buf, MAXLINE, stdin)) {
		if (line++ == 1) strcpy(my_ticket, buf);
		// move pointer ahead to numbers
		else if (line < 5) continue;
		else {
			get_nums(buf);
			memset(buf, 0, MAXLINE);
		}
	}
	printf("%d\n", t_count);

	
	for (int g = 0; g < t_count; g++) {
		printf("%s\n", tickets[g]);
		check_good_tkts(tickets[g], g);
	}
	for (int z = 0; z < t_count; z++) {
		for (int x = 0; x < 20; x++) {
			printf("%d, ", check_rules[z][x]);
		}
		printf("\n");
	}
	
	printf("part 1: %ld\n", total);
	return 0;


	// loop through each column (i.e. ticket[i][j])
	

	// test that number against each rule
	// break if one test fails
	// if column passes each test, that column corresponds to that rule
}
