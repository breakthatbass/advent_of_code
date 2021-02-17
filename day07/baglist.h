#ifndef __BAGLIST_H__
#define __BAGLIST_H__

#define BAGSIZE 30

typedef struct sub_bag {
	char sub_bag_name[BAGSIZE];
	int count;
} sub_bag_t;


typedef struct _bag {
	char bag_name[BAGSIZE];
	sub_bag_t sub_bags[10];
	int sub_bags_len;
	struct _bag *next;
} bag_t;


typedef struct head {
	bag_t *head;
	int bags;
} list_t;


// BAG LIST API

list_t *list_init(void);

// add a bag_t node to the list
void push(list_t *list, char *bag);

// print bags is for testing the list
// it prints each main bag and its sub bags
void print_bags(list_t *list);

#endif
