#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NBUSES 10
#define MAXLINE 200

int main()
{

	char buf[MAXLINE];
	int earliest_t, len, i;
	int *bus_ids = malloc(sizeof(int)*NBUSES);
	char *n;

	// get earliest timestamp
	fgets(buf, MAXLINE, stdin);
	earliest_t = atoi(buf);

	// get the bus ids
	fgets(buf, MAXLINE, stdin);

	// append first bus id
	n = strtok(buf, ",");
	bus_ids[0] = atoi(n);

	// get the rest
	i = 1; len = 1;
	while ((n = strtok(NULL, ",")) != NULL) {
		if (strcmp(n, "x") == 0) continue;
		bus_ids[i++] = atoi(n);
		len++;
	}

	int t, w;
	int lowest_b;
	int lowest_t = INT_MAX;
	for (i = 0; i < len; i++) {
		t = bus_ids[i];
		w = bus_ids[i] - (earliest_t % bus_ids[i]);
		if (w < lowest_t) {
			lowest_t = w;
			lowest_b = bus_ids[i];
		}
	}
	
	printf("part 1: %d\n", lowest_t*lowest_b);  // not 1938765
	//free(bus_ids);
	


	return 0;
}
