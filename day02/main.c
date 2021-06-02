#include <stdio.h>
#include <assert.h>

#include "../timing.h"

#define LINE 50

int sled(int min, int max, char c, char *pass)
{
    int count = 0;
    while (*pass) {
        if (*pass == c) count++;
        pass++;
    }
    if (count >= min && count <= max)
        return 1;
    return 0;
}

int toboggan(int min, int max, char c, char *pass)
{
    if (pass[min-1] == c ^ pass[max-1] == c)
        return 1;
    return 0;
}

int main()
{
    int min, max;
    char c;
    char pass[LINE];

    int valid_sled = 0;
    int valid_toboggan = 0;

    timing t;

    start_timing(&t);
    while (fscanf(stdin, "%d-%d %c: %s", &min, &max, &c, pass) == 4) {
        valid_sled += sled(min, max, c, pass);
        valid_toboggan += toboggan(min, max, c, pass);
    }
    end_timing(&t);

    assert(valid_sled == 582);
    assert(valid_toboggan == 729);

	printf("valid sled passwords: %d\n", valid_sled);
	printf("valid toboggan passwords: %d\n", valid_toboggan);
    printf("total time: %f\n", t.ttime);

    return 0;
}
