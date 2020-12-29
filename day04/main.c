#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 500
char fields[][4] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};    

// get_val: extract the value from desired field
char *get_val(char *passport, char *field)
{
	char *t;
	char *s;  // hold pointer after field
	char *cs; // hold pointer from s after ':'
	
	// copy passport as to not mutilate original
	char *cpy = malloc(sizeof(char)*strlen(passport)+1);
	strcpy(cpy, passport);
	if ((s = strstr(cpy, field))) {
		cs = strstr(s, ":");
		memmove(cs, cs+1, strlen(cs));
		t = strtok(cs, " \n");
	}
	free(cpy);
    return t;
}


// check_passport: verify if contains required fields
int check_passport(char *passport)
{
	for (int i = 0; i < 7; i++) {
		if (strstr(passport, fields[i]) == NULL)
			return 0;
	}
	return 1;
}


// check each value and determine if they fall within parameters
int extra_validation(char *passport)
{
	// make sure all fields are present
	if (check_passport(passport) == 0) return 0;

	int n, i;
	char *s, *cs, *t;

	int vf = 0;	// validated fields count. need 7

	for (i = 0; i < 7; i++) {
		s = get_val(passport, fields[i]);
		// now we check each field...
		
		// BIRTH YEAR
		if (strcmp(fields[i], "byr") == 0) {
			int n = atoi(s);
			if (n < 1920 || n > 2002) return 0;
			else vf++;
		}
		// ISSUE YEAR
		else if (strcmp(fields[i], "iyr") == 0) {
			int n = atoi(s);
			if (n < 2010 || n > 2020) return 0;
			else vf++;
		}
		// EXPIRATION YEAR
		else if (strcmp(fields[i], "eyr") == 0) {
			int n = atoi(s);
			if (n < 2020 || n > 2030) return 0;
			else vf++;
		}
		// HEIGHT
		else if (strcmp(fields[i], "hgt") == 0) {
			if (strstr(s, "cm")) {
				//printf("%s: ", s);
				char *t = strtok(s, "c");
				//printf("%s\n", t);
				int n = atoi(t);
				if (n < 150 || n > 193) return 0;
			} else if (strstr(s, "in")) {
				char *t = strtok(s, "i");
				int n = atoi(t);
				if (n < 59 || n > 76) return 0;
			}
			vf++;
		}
		// HAIRCOLOR
		else if (strcmp(fields[i], "hcl") == 0) {
			size_t len = strlen(s);
			// must start with '#' and have 7 characters
			if (s[0] != '#' || len != 7) return 0;
			for (int i = 0; i < len; i++) {
				if (s[i] < 0 || s[i] > 9) continue;
				else if (s[i] < 'a' && s[i] > 'f') continue;
				else return 0;
			}
			vf++;
		}
		// EYE COLOR
		else if (strcmp(fields[i], "ecl") == 0) {
			// valid eye colors
			int found = 0;
			char eyc[][7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
			for (int i = 0; i < 7; i++) {
				if (strcmp(s, eyc[i]) == 0) {
					found = 1;
					break;
				}
			}
			if (found == 1) vf++;
			else return 0;
		}
		else {
			// PASSPORT ID
			if (strcmp(fields[i], "pid") == 0) {
				if (strlen(s) != 9) return 0;
				vf++;
			}
		}
	}
	if (vf != 7) return 0;
	return 1;
}


int main()
{
	char buf[MAXLINE];
	int i, c;
	
	int valid = 0;
	int extra_valid = 0;
	i = 0;

	while ((c = fgetc(stdin))) {
		if (buf[i-1] == '\n' && c == '\n') {
			valid += check_passport(buf);
			extra_valid += extra_validation(buf);
			i = 0;
			memset(buf, 0, MAXLINE);
		} else if (feof(stdin)) {
			// we're at the last passport
			valid += check_passport(buf);
			extra_valid += extra_validation(buf);
			break;
		} else buf[i++] = c;
	}

	printf("part 1: %d\n", valid);
	printf("part 2: %d\n", extra_valid);

	return 0;
}
