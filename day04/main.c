#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../timing.h"
#include "../lib/split.h"   /* split, len */
#include "../lib/strlib.h"  /* strafter, cpy_until */


#define MAXLINE 500
#define MAXPASS 1096

static const char *fields[7] = {
    "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"
};

#define LEN() (sizeof(fields)/sizeof(fields[0]))

int validate(char *s)
{
    int field_count = 0;

    for (unsigned long i = 0; i < LEN(); i++) {
        if (strstr(s, fields[i]))
            field_count++;
    }

    if (field_count == 7)
        return 1;
    return 0;
}

int extra_validation(char *s)
{
    char **split_pass;
    char *tmp;
    int n;

    /* split: split a string into sep strings based on delimiter(s) - ' ' and '\n' */
    split_pass = split(s, " \n");
    print_arr(split_pass);
    printf("-----\n\n");
    return 1;

    int i = 0;

    if (len(split_pass) < 7) goto fail;
    /* strafter: search str for substring, if found, move pointer to after sunstring */
    while (*split_pass) {

        /* birth year */
        if ((tmp = strafter(*split_pass, "byr:"))) {
            n = atoi(tmp);
            if (n < 1920 || n > 2002) goto fail;

        /* issue year */
        } else if ((tmp = strafter(*split_pass, "iyr:"))) {
            n = atoi(tmp);
            if (n < 2010 || n > 2020) goto fail;

        /* expiration year */
        } else if ((tmp = strafter(*split_pass, "eyr:"))) {
            n = atoi(tmp);
            if (n < 2020 || n > 2030) goto fail;
        
        /* height */
        } else if ((tmp = strafter(*split_pass, "hgt:"))) {
            if (strstr(*split_pass, "cm")) {
                char t[10];
                cpy_until(t, tmp, 'c');
                n = atoi(t);
                if (n < 150 || n > 193) goto fail;
            } else if (strstr(*split_pass, "in")) {
                char t[10];
                cpy_until(t, tmp, 'i');
                n = atoi(t);
                if (n < 59 || n > 76) goto fail;
            } else goto fail;

        /* hair color */
        } else if ((tmp = strafter(*split_pass, "hcl:"))) {
            if (*(tmp++) != '#') goto fail;
            
            while (*tmp) {
                if (!(*tmp >= '0' && *tmp <= '9') &&
			    !(*tmp >= 'a' && *tmp <= 'f')) goto fail;
                tmp++;
            }
        
        /* eye color */
        } else if ((tmp = strafter(*split_pass, "ecl:"))) {
            //printf("ecl: %s\n", tmp);
            if (
                strcmp(tmp, "amb") && strcmp(tmp, "blu") &&
                strcmp(tmp, "brn") && strcmp(tmp, "gry") &&
		        strcmp(tmp, "grn") && strcmp(tmp, "hzl") &&
		        strcmp(tmp, "oth")
            ) goto fail;
            //printf("\t->passed: %s\n", tmp);
        
        /* passport ID */
        } else if ((tmp = strafter(*split_pass, "pid:"))) {
            if (strlen(tmp) != 9) goto fail;
        }
        split_pass++;
        i++;
        tmp = NULL;
    }
    split_pass -= i;
    free(split_pass);
    return 1;

fail:
    split_pass -= i;
    free(split_pass);
    return 0;
}


int main()
{
    char buf[MAXLINE];
    char passport[MAXPASS];
    char *s;
    timing t;

    int valid = 0;
    int extra_valid = 0;

    start_timing(&t);
    while ((s = fgets(buf, MAXLINE, stdin))) {
        if (strcmp(buf, "\n") != 0) {
            if (passport[0] == 0) 
                strcpy(passport, buf);
            else 
                strcat(passport, buf);
        } else {
            valid += validate(passport);
            extra_valid += extra_validation(passport);
            memset(passport, 0, MAXPASS);
        }
    }
    /* we exit the loop before the last passport is processed */
    valid += validate(passport);
    extra_valid += extra_validation(passport);
    end_timing(&t);
    
    assert(valid == 182);
    //assert(extra_valid == 109);

    printf("part1: %d\n", valid);
    printf("part2: %d\n", extra_valid);
    printf("total time: %f\n", t.ttime);
    
    return 0;
}
