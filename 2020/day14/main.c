// not done

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBITS 37
#define MAXLINE 1000
#define MEMSIZE 70000

struct mem {
    uint64_t loc;
    uint64_t val;
}; typedef struct mem mem;


// load_struct: parse string to get memory location and its value
mem load_struct(char *line)
{
    mem m;
    sscanf(line, "mem[%llu] = %llu", &m.loc, &m.val);
    return m;
}

int main()
{
    uint64_t *memory = calloc(MEMSIZE, sizeof(uint64_t));
    char mask[NBITS];
    char buf[MAXLINE];
    int total = 0;

    int c;
    int i, p = 0;
    while ((c = fgetc(stdin)) != EOF) {
        if (c == '\n') {
            if (strstr(buf, "mask")) {
                // move pointer ahead to the value of mask
                memmove(buf, buf+7, strlen(buf));
                strcpy(mask, buf);
            }
            else if (strstr(buf, "mem")) {
                mem m = load_struct(buf);
                memory[m.loc] = m.val;
            }
            i = 0;
            memset(buf, 0, MAXLINE);
        } else buf[i++] = c;
    }


    for (uint64_t j = 0; j < MEMSIZE; j++) {
        //if (memory[j] != 0) 
        //printf("%llu: %llu\n", j, memory[j]);
    }
    free(memory);


    return 0;
}