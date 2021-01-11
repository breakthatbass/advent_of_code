#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../lib/converters.h"

#define MASK 33



char *apply_mask(char *mem, char *mask)
{
    // we have to AND some value and OR some values
    char *new_bin = malloc(sizeof(char)*MASK)+2;
    while (*mem++ && *mask++) {
        // if X we keep the mem value
        if (*mask == 'X') *new_bin++ = *mem;
        else if (*mask == '0') *new_bin++ = '0';
        else if (*mask == '1') *new_bin++ = '1';
        else *new_bin++ = *mem;
    }
    *new_bin = '\0';
    new_bin -= MASK-1;
    printf("MASKED: %s\n", new_bin);
    return new_bin;
}


int main()
{
    static char buf[128];
    char *c;
    uint64_t cur_mask;
    uint64_t mem;
    char *msk; //= malloc(sizeof(char)*MASK);

    uint64_t total = 0;

    while(fgets(buf, 128, stdin)) {
        // replace \n with \0
        c = strchr(buf, '\n');
        *c = '\0';
        if (strncmp(buf, "mask", 4) == 0) {
            msk = strchr(buf, '=');
            msk += 2; // move pointer ahead to bit mask.

            printf("mask: %s\n", msk);
            //cur_mask = btod(c);
        } else if (strncmp(buf, "mem", 3) == 0) {
            c = strchr(buf, '=');
            c += 2; // move pointer ahead to numbers
            mem = atoi(c);  // never use this!
            printf("mem: %llu\n", mem);
            char *pp = dtob(mem);
            char *poo = pad_bin(pp);
            printf("mem binary: %s\n", pp);
            printf("mem padded: %s\n", poo);
            char *p = apply_mask(poo, msk);
            //printf("%s\n", p);
        }
    }
    printf("PART 1: %llu\n", total/2);  // 9659578589 too low
    return 0;
}










