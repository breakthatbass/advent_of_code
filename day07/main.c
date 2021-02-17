#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "baglist.h"

#define MAXLINE 1028
#define LINES 595
#define BAGSIZE 30

// parse the bag line and add bags to the linked list
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
		
		sub_bag_t *bag = malloc(sizeof(sub_bag_t));
		assert(bag);
		
		strcpy(bag->sub_bag_name, main_bag);
		bag->count = n;

		list->head->sub_bags[i++] = *bag;

		memset(adj, 0, BAGSIZE);
		memset(col, 0, BAGSIZE);
		memset(main_bag, 0, BAGSIZE);

		// we're done with the bag structure until the next loop
		free(bag);

		// check for more bags
		ptr  = strstr(ptr, ", ");
		if (ptr == NULL) break;
		else ptr += 2;
	}
	list->head->sub_bags_len = i;
}

int shiny_gold_bags(list_t *list, char *bag)
{
	sub_bag_t *t;
	int count = 0;
	bag_t *tmp = bagsearch(list, bag);
	if (tmp == NULL) return 0;
	// if there are no sub bags, move on
	if (tmp->sub_bags_len == 0) return 0;

	// else seach sub bags for shiny gold bag
	t = tmp->sub_bags;
	for (int j = 0; j < tmp->sub_bags_len; j++) {
		if (strcmp(t[j].sub_bag_name, "shiny gold") == 0)
			count++;
		count += shiny_gold_bags(list, t[j].sub_bag_name);
	}
	return count;
}

int bag_count(list_t *list, char *bag)
{
	int count = 0;
	sub_bag_t *t;
	bag_t *new_bag = bagsearch(list, bag);
	
	// we start with our gold bag and work through the list
	if (new_bag->sub_bags_len == 0) return 0;

	t = new_bag->sub_bags;
	for (int j = 0; j < new_bag->sub_bags_len; j++) {
		count += t[j].count;
		count += t[j].count * bag_count(list, t[j].sub_bag_name);
	}
	return count;
}



int main(void)
{
	char line_buf[MAXLINE];
	
	list_t *list = list_init();

	while (fgets(line_buf, MAXLINE, stdin)) {
		line_buf[strcspn(line_buf, "\n")] = 0;
		parse(list, line_buf);
	}

	int total_gold = 0;
	bag_t *tmp = list->head;
	while (tmp) {
		if (shiny_gold_bags(list, tmp->bag_name) > 0)
			total_gold++;
		tmp = tmp->next;
	}

	int bagtotal = bag_count(list, "shiny gold");
	
	printf("part 1: %d\n", total_gold);
	printf("part 2: %d\n", bagtotal);

	free(list);
	return 0;
}

