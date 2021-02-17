#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "baglist.h"

#define MAXLINE 1028
#define LINES 595
#define BAGSIZE 30


void parse(list_t *list, char *line)
{
	char main_bag[BAGSIZE];
	char adj[BAGSIZE], col[BAGSIZE];
	int n;

	sscanf(line, "%s %s", adj, col);
	strcpy(main_bag, adj);
	strcat(main_bag, " ");	// get a space between the words
	strcat(main_bag, col);

    push(list, main_bag);
	printf("NEW BAG: %s\n", list->head->bag_name);

    // get the sub bags
	char *ptr = strstr(line, "contain");  // bring the pointer to 'contain'
	ptr += 8;	// move the pointer ahead to the first sub bag

    // quit working if there are no sub bags
	if (strcmp(ptr, "no other bags.") == 0) {
		return;
	}

	memset(adj, 0, BAGSIZE);
	memset(col, 0, BAGSIZE);
	memset(main_bag, 0, BAGSIZE);

	// while there are sub bags, link them to the current bag_t node
	int i = 0;
	while (sscanf(ptr, "%d %s %s", &n, adj, col)) {
		strcpy(main_bag, adj);
		strcat(main_bag, " ");	// get a space between the words
		strcat(main_bag, col);
		//printf("made it here\n");
		printf("\t--> %d %s\n", n, main_bag);
		// create new sub bag and add to current main bag list
		//append_sub_bag(list, n, main_bag);
		sub_bag_t *bag = malloc(sizeof(sub_bag_t));
		assert(bag);
		//bag->sub_bag_name = main_bag;
		strcpy(bag->sub_bag_name, main_bag);
		//bag->sub_bag_name = main_bag;
		bag->count = n;

		list->head->sub_bags[i++] = *bag;

		memset(adj, 0, BAGSIZE);
		memset(col, 0, BAGSIZE);
		memset(main_bag, 0, BAGSIZE);

		// check for more bags
		ptr  = strstr(ptr, ", ");
		if (ptr == NULL) {
			break;
		} else {
			ptr += 2;
		}
	}
	list->head->sub_bags_len = i;
}

int main(void)
{
	char line_buf[MAXLINE];

	FILE *fp = fopen("input", "r");
	assert(fp);
	
	list_t *list = list_init();

	while (fgets(line_buf, MAXLINE, fp)) {
		line_buf[strcspn(line_buf, "\n")] = 0;
		parse(list, line_buf);
		printf("%s\n", line_buf);
		printf("\n\n");
	}

	printf("...\n...\n");

	print_bags(list);

	free(list);
	return 0;
}

