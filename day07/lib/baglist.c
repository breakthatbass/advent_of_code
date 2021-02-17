#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "baglist.h"

list_t *list_init(void)
{
	list_t *l = malloc(sizeof(list_t));
	assert(l);

	l->head = NULL;
	l->bags = 0;

	return l;
}

static bag_t *new_bag(char *bag)
{
    bag_t *b = malloc(sizeof(bag_t));
    assert(b);

    strcpy(b->bag_name, bag);
    //b->sub_bags = NULL;
    b->next = NULL;

    return b;
}


void push(list_t *list, char *bag)
{
    bag_t *n = new_bag(bag);

	n->next = list->head;
    list->head = n;
    list->bags++;
}

void print_bags(list_t *list)
{
    sub_bag_t *t;
	bag_t *tmp = list->head;
	int i = 1; // number each main bag

	while (tmp) {
        // print the main bag
		printf("%d: %s\n", i++, tmp->bag_name);
		
        // print the sub bags
        t = tmp->sub_bags;
		for (int j = 0; j < tmp->sub_bags_len; j++) 
			printf("\t%d %s\n", t[j].count, t[j].sub_bag_name);
	
		tmp = tmp->next;
	}
}


// search the list for a bag, return that node
bag_t *bagsearch(list_t *list, char *bag)
{
    bag_t *tmp = list->head;
    while (tmp) {
        if (strcmp(tmp->bag_name, bag) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
