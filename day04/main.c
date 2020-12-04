#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#include "../helpers.h"

#define PLEN 7
#define FLEN 4


// check_passport: verify if contains required fields
int check_passport(char *passport)
{
    char fields[PLEN][FLEN] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    
    for (int i = 0; i < PLEN; i++) {
        if (strstr(passport, fields[i]) == NULL)
            return 0;
    }
    return 1;
}

char *get_val(char *passport, char *field, int len)
{
    int n;
    char *s;  // holds ptr to passport after field
    char *cs;   
    char *t;  // holds just the field value

    if ((s = strstr(passport, field))) {
        cs = strstr(s, ":");
        *cs++; // move ahead one space after the ':'
        t = malloc(sizeof(char)*len+1);
        t = strncpy(t, cs, len);
    }
    return t;
}

int check_byr(char *passport, char *field)
{
    char *s = get_val(passport, field, 4);
    int n = atoi(s);
    if (n < 1920 || n > 2002) return 0;

    printf("byr VALID\n");
    
    return 1;
}

int check_iyr(char *passport, char *field)
{
    char *s = get_val(passport, field, 4);
    int n = atoi(s);
    if (n < 2010 || n > 2020) return 0;
    printf("iyr VALID\n");
    return 1;
}

int check_eyr(char *passport, char *field)
{
    char *s = get_val(passport, field, 4);
    int n = atoi(s);
    if (n < 2020 || n > 2030) return 0;

    printf("eyr VALID\n");
    
    return 1;

}

int check_hgt(char *passport, char *field)
{
    char *s = get_val(passport, field, 8);
    char *hgt = strtok(s, " ");
    int len = strlen(hgt)-1;
    if ((hgt[len-2] == 'c' || hgt[len-2] == 'i') && (hgt[len-1] == 'm' || hgt[len-1] == 'n')) {
        if (hgt[len-2] == 'c') {
            char *cs = strtok(hgt, "c");
            int n = atoi(cs);
            if (n < 150 || n > 193) return 0;
        }
        else {
            char *cs = strtok(hgt, "i");
            int n = atoi(cs);
            if (n < 59 || n > 76) return 0;
        }
    } else return 0;
    printf("hgt VALID\n");
    return 1;
}

int check_hcl(char *passport, char *field)
{
    char *s = get_val(passport, field, 7);
    size_t len = strlen(s);
    if (s[0] != '#' || len != 7) return 0;
    
    for (int i = 1; i < len; i++) {
        if (s[i] < 0 || s[i] > 9) continue;
        else if (s[i] < 'a' && s[i] > 'f') continue;
        else return 0;
    }
    printf("hcl VALID\n");
    return 1;
}

int check_ecl(char *passport, char *field)
{
    char eyc[PLEN][FLEN] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"}; 
    char *s = get_val(passport, field, 3);
    for (int i = 0; i < PLEN; i++) {
        //printf("%s\n", eyc[i]);
        if (strcmp(s, eyc[i]) == 0) {
            printf("%s is VALID\n", s);
            return 1;
        }
    }
    
    return 0;
}

int check_pid(char *passport, char *field)
{
    // get_val and strtok will eliminate anything more than 9 digits
    char *s = get_val(passport, field, 15);
    char cs[10];
    strncpy(cs, s, 10);
    printf("cs[9] : %c\n", cs[9]);
    //if (cs[9] != '\n' || cs[9] != ' ' || cs[9] != '\0') return 0;
    //printf("PID : %s\n", cs);
    
    for (int i = 0; i < 8; i++) {
        if (isdigit(cs[i]) == 0) return 0;
    }
    printf("pid VALID\n");
    
    return 1;
}

int extra_validation(char *passport)
{
    // make sure all fields are present
    if (check_passport(passport) == 0) return 0;

    int n;
    char *s;  // holds ptr to passport after field
    char *cs;   
    char *t;  // holds just the field value
    char fields[PLEN][FLEN] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    int vf = 0; //validated fields. need 7
    
    for (int i = 0; i < PLEN; i++) {
        if (strcmp(fields[i], "byr") == 0) {
            if (check_byr(passport, fields[i]) == 0) return 0;
            else vf++;
        }
        else if (strcmp(fields[i], "iyr") == 0) {
            if (check_iyr(passport, fields[i]) == 0) return 0;
            else vf++;
        }
        else if (strcmp(fields[i], "eyr") == 0) {
            if (check_eyr(passport, fields[i]) == 0) return 0;
            else vf++;
        }
        else if (strcmp(fields[i], "hgt") == 0) {
            if (check_hgt(passport, fields[i]) == 0) return 0;
            else vf++;
        }
        else if (strcmp(fields[i], "hcl") == 0) {
            if (check_hcl(passport, fields[i]) == 0) return 0;
            else vf++;
        }
        else if (strcmp(fields[i], "ecl") == 0) {
            if (check_ecl(passport, fields[i]) == 0) return 0;
            else vf++;
        } 
        else {
            if (check_pid(passport, fields[i]) == 0) return 0;
            else vf++;
        }
    }

    if (vf != 7) return 0;

    return 1;
}


int main(int argc, char **argv)
{
    if (argc != 2) errmsg("usage: ./passport <input-file>");

	char *file = argv[1];

    // file_ptr opens file, error checks, returns ptr
    FILE *fp = file_ptr(file);
   
    int c;
    int i = 0;
    long valid = 0; 
    int more_valid = 0;
    char buffer[MAXLINE];
    while ((c = fgetc(fp))) {
        // detect a blank line indicating we've got a passport
        if (buffer[i-1] == '\n' && c == '\n') {
            
            //printf("%s\n", buffer);
            valid += check_passport(buffer);
            more_valid += extra_validation(buffer);
            memset(buffer, 0, MAXLINE);
            i = 0;
        } else if (feof(fp)) {
            // we're at the end of file
            // verify last passport
            //printf("%s\n", buffer);
            valid += check_passport(buffer);
            more_valid += extra_validation(buffer);
            break;
        } else {
            buffer[i++] = (char)c;
        }
    }

    printf("valid passports: %lu\n", valid);
    printf("TRULY valid passports: %d\n", more_valid);
    
    fclose(fp);
    return 0;
}
