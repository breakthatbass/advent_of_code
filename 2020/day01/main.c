#include <stdio.h>
#include <assert.h>

#define LEN 200

static int part1;
static int part2;

// messy but it's efficient
void count(int *n)
{
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			if (i == j) continue;
			if (n[i] + n[j] == 2020) 
				part1 = n[i] * n[j];
			for (int k = 0; k < LEN; k++) {
				if (i == j && i == k) continue;
				if (n[i] + n[j] + n[k] == 2020) {
					part2 = n[i] * n[j] * n[k];
					return;
				}
			}
		}
	}
}


int main()
{

    int nums[LEN];
    int i = 0;
    while (fscanf(stdin, "%d", &nums[i++]) == 1);

	count(nums);

	assert(part1 == 157059);
	assert(part2 == 165080960);
	
    return 0;
}
