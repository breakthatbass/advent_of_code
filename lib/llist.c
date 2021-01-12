#include "llist.h"
#include <stdio.h>
#include <stdlib.h>


// new_node: creates new node for list
node_t *new_node(int value)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        fprintf(stderr, "llist: not enough space to add %d\n", value);
        exit(1);
    }
    node->value = value; 
    node->next = NULL;

    return node;
}


// append: add node to end of list
void append(node_t **head, int value)
{
    node_t *node = new_node(value);

    if (*head == NULL) {
        node->next = *head;
        *head = node;
    } else {
        node_t *tmp = *head;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
}


// pull: pull first node from list
int pull(node_t **head)
{
    int n;  // return value

    if (head == NULL) return -1;
    else {
        node_t *tmp = *head;
        n = tmp->value;
        *head = tmp->next;
        free(tmp);
    }
    return n;
}


// print: print list with position of each element
void printlist(node_t *head)
{
    node_t *tmp = head;
    int i = 1;

    while (tmp != NULL)
    {
        printf("%d: %d\n", i++, tmp->value);
        tmp = tmp->next;
    }
}
