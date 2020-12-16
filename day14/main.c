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

char *convert(uint64_t val)
{
    static char b[NBITS];
    int i = 0;
    while (val > 0) {
        b[i++] = val % 2;
        val /= 2;
    }
    return b;
}


// load_struct: parse string to get memory location and its value
mem load_struct(char *line)
{
    mem m;
    sscanf(line, "mem[%llu] = %llu", &m.loc, &m.val);
    return m;
}

void do_mask(char *mask, uint64_t val)
{
    char *b = malloc(sizeof(int)*NBITS);
    b = convert(val);
    printf("%s\n", b);
    int i;
    for (i = 0; i < NBITS; i++) {
        if (mask[i] == '1') {

        }
    }
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
                do_mask(mask, m.val);
            }
            i = 0;
            memset(buf, 0, MAXLINE);
        } else buf[i++] = c;
    }


    for (uint64_t j = 0; j < MEMSIZE; j++) {
        if (memory[j] != 0) 
        printf("%llu: %llu\n", j, memory[j]);
    }
    free(memory);


    return 0;
}