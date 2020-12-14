// not done

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBITS 36
#define MAXLINE 1000
#define MEMSIZE 999000000



struct mem {
    uint64_t loc;
    uint64_t value;
} mem;

mem *memory = (mem*)calloc(MEMSIZE, sizeof(mem));


int main()
{
    char mask[NBITS+1];
    uint64_t mem_val;
    char buf[MAXLINE];
    int total = 0;
    int i = 0;

    int l = 0;

    int c, p;
    while ((c = fgetc(stdin)) != EOF) {
        if (c == '\n') {
            if (strstr(buf, "mask")) {
                // move pointer ahead to the value of mask
                memmove(buf, buf+7, strlen(buf));
                strcpy(mask, buf);
                //printf("%s\n", mask);
            }
            else if (strstr(buf, "mem")) {
                p = 0;
                while (buf[p++] != '=');
                // move the pointer ahead to value of mem
                memmove(buf, buf+p+1, strlen(buf));
                mem_val = atoi(buf);
                if (mem_val > l) l = mem_val;
                printf("MEM VALUE: %llu\n", mem_val);
                printf("BINARY: ");
                convert(mem_val);

            }
            i = 0;
            memset(buf, 0, MAXLINE);

        } else buf[i++] = c;
    }

    // get mask
    // convert mem value to binary
    // OR the mask to the binary value
    // covert back to decimal
    // add that decimal mem value to total
    printf("LARGEST: %d\n", l);
    return 0;
}