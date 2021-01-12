#ifndef __LLIST_H__
#define __LLIST_H__

#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;


/*** PROTOTYPES ***/

// new_node: create a new node for the list
node_t *new_node(int card);

// append: add node to end of list
void append(node_t **head, int value);

// pull: pull a node from the front
int pull(node_t **head);

// print: print list with position of each element
void printlist(node_t *head);

#endif
