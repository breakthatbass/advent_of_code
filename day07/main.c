#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXLINE 1028
#define LINES 595
#define BAGSIZE 25

typedef struct sub_bag {
	char sub_bag_name[BAGSIZE];
	int count;
	struct sub_bag *next_bag;
} sub_bag_t;

// a linked list of bags with pointers to nodes contains sub bag info
typedef struct _bag {
	char bag_name[BAGSIZE];
	sub_bag_t *sub_bags;
	struct _bag *next;
} bag_t;

typedef struct head {
	bag_t *head;
	int bags;
} list_t;

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
    b->sub_bags = NULL;
    b->next = NULL;

    return b;
}

static sub_bag_t *new_sub(char *bag, int count)
{
	sub_bag_t *b = malloc(sizeof(sub_bag_t));
	assert(b);

	strcpy(b->sub_bag_name, bag);
	b->count = count;
	b->next_bag = NULL;

	return b;
}

void append_sub_bag(list_t *list, int count, char *bag)
{
	sub_bag_t *b = new_sub(bag, count);

	//sub_bag_t *tmp = list->head->sub_bags;
	if (list->head->sub_bags == NULL) {
		//printf("in here!\n");
		list->head->sub_bags = b;
		printf("first add...\n");
		printf("\t--- %d %s\n", list->head->sub_bags->count, list->head->sub_bags->sub_bag_name);
	} else {
		b->next_bag = list->head->sub_bags;
		list->head->sub_bags->next_bag = b;
		//printf("\t--- %d %s\n", b->count, b->sub_bag_name);
		printf("\t--- %d %s\n", list->head->sub_bags->count, list->head->sub_bags->sub_bag_name);
	}
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
	bag_t *tmp = list->head;
	sub_bag_t *t;
	int i = 1;

	while (tmp != NULL) {
		printf("%d: %s\n", i++, tmp->bag_name);
		t = tmp->sub_bags;
		while (t) {
			printf("\t%d %s\n", t->count, t->sub_bag_name);
			t = t->next_bag;
		}
		tmp = tmp->next;
	}
}

//////////

void parse(list_t *list, char *line)
{
	char main_bag[BAGSIZE];
	char adj[10], col[10];
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

	memset(adj, 0, 10);
	memset(col, 0, 10);
	memset(main_bag, 0, BAGSIZE);

	// while there are sub bags, link them to the current bag_t node
	while (sscanf(ptr, "%d %s %s", &n, adj, col)) {
		strcpy(main_bag, adj);
		strcat(main_bag, " ");	// get a space between the words
		strcat(main_bag, col);
		//printf("made it here\n");
		printf("\t--> %d %s\n", n, main_bag);
		// create new sub bag and add to current main bag list
		append_sub_bag(list, n, main_bag);

		memset(adj, 0, 10);
		memset(col, 0, 10);
		memset(main_bag, 0, BAGSIZE);

		ptr  = strstr(ptr, ", ");
		if (ptr == NULL) {
			break;
		} else {
			ptr += 2;
		}
	}
}

int main(void)
{
	char line_buf[MAXLINE];

	FILE *fp = fopen("input_test", "r");
	
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

