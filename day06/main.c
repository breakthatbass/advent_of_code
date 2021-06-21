#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../timing.h"

#define BUF 1024
#define MAXALPHA 28


// count_yes: read through answers, count the number of unique answers
size_t count_yes(char *s)
{
	char answers[MAXALPHA] = {0};
	int len = 0;
	
	// add any char that isn't already in answers
	while (*s) {
		if (strchr(answers, *s) == NULL && *s != '\n') {
			answers[len++] = *s;
		}
		s++;
	}
	return len;
}


// get the number of people in a group
int count_people(char *s)
{
	int count = 0;

	while (*s) {
		if (*s == '\n') count++;
		s++;
	}
	return count;
}


// get the number of times char c is in str s
int count_chars(char *s, char c)
{
	int count = 0;

	while (*s) {
		if (*s == c) count++;
		s++;
	}
	return count;
}


// get the number of answers that all people in group answered yes
int all_yes(char *s)
{
	int people, chars, total;

	total = 0;
	people = count_people(s);
	
	while (*s) {
		if (*s != '\n') {
			chars = count_chars(s, *s);
			if (chars == people) total++;
		}
		s++;
	}
	return total;
}



int main()
{
	char buf[BUF];
	char group[BUF] = {0};
	size_t part1_total = 0;
	int part2_total = 0;
	timing t;

	start_timing(&t);
	while (fgets(buf, BUF, stdin)) {
		if (strcmp(buf, "\n") != 0) {
			if (group[0] == 0)
				strcpy(group, buf);
			else
				strcat(group, buf);
		} else {
			all_yes(group);
			part1_total += count_yes(group);
			part2_total += all_yes(group);
			memset(group, 0, BUF);
		}
	}
	// last group can't be accessed in while loop
	part1_total += count_yes(group);
	part2_total += all_yes(group);

	end_timing(&t);

	assert(part1_total == 6587);
	assert(part2_total == 3235);

	printf("part 1: %zu\n", part1_total);
	printf("part 2: %d\n", part2_total);
	printf("total time: %f\n", t.ttime);

	return 0;
}
