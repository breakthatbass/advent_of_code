#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/converters.h" // btod dtob

#define MASK 37
#define MEMCAP 600

struct memcell {
    uint64_t addr;
    uint64_t val;
};
static int size; // keep track of placement

// store mem addresses and their masked values
static struct memcell memory[MEMCAP];


char *apply_mask(char *mem, char *mask)
{
    size_t i;
    static char new_bin[MASK];
    size_t len = strlen(mask);

    for (i = 0; i < len; i++) {
        if (mask[i] == 'X') new_bin[i] = mem[i];
        else if (mask[i] == '0') new_bin[i] = '0';
        else if (mask[i] == '1') new_bin[i] = '1';
        else new_bin[i] = mem[i];
    }
    return new_bin;
}


// add a mem addr and mem val to the memcell array
void insert_mem(uint64_t addr, uint64_t val)
{
    int i;
    for (i = 0; i < size; i++) 
        if (memory[i].addr == addr) break;
    
    if (i == size) memory[size++].addr = addr;

    memory[i].val = val;
}

uint64_t memcount(void)
{
    int i;
    uint64_t total = 0;
    for (i = 0; i < size; i++) {
        printf("addr: %llu  val: %llu\n", memory[i].addr, memory[i].val);
        total += memory[i].val;
    }
    return total;
}


int main()
{
    static char buf[128];
    char *c;
    char *msk = malloc(sizeof(char)*MASK);

    uint64_t total = 0;

    while(fgets(buf, 128, stdin)) {
        // replace \n with \0
        c = strchr(buf, '\n');
        *c = '\0';
       
        if (strncmp(buf, "mask", 4) == 0) {
            strcpy(msk, strchr(buf, '='));
            msk += 2; // move pointer ahead to bit mask.


        } else if (strncmp(buf, "mem", 3) == 0) {
            int mem_addr;
            sscanf(buf, "mem[%d", &mem_addr);

            c = strchr(buf, '=');
            c += 2; // move pointer ahead to numbers
            
            
            char *mem_bin = dtob(atoi(c));
            char *bin36 = pad_bin(mem_bin);
            char *masked_mem = apply_mask(bin36, msk);

            insert_mem(mem_addr, btod(masked_mem));
        }
    }
    total = memcount();
    printf("PART 1: %llu\n", total);
    return 0;
}










