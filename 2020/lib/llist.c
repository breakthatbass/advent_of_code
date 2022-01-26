#include <stdio.h>
#include <stdlib.h>

#include "llist.h"


// list_init: initiate a linked list
list_t *list_init(void)
{
    list_t *l = malloc(sizeof(list_t));
    if (l == NULL) {
        perror("list_init:");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    l->nodes = 0;

    return l;
}


/* *
 *	new_node:
 *	
 *	DESCRIPTION:
 *		allocate space for a new node in a list. if allocation is successful,
 *		add the value to the node and connect it to list.
 *
 *	RETURN VALUE:
 *		returns the node even if allocation is unsuccessful. error checking is
 *		done outside of the function.
 *
 * */
static node_t *new_node(int value, node_t *next)
{
    node_t *node = malloc(sizeof(node_t));

    if (node != NULL) {
        node->value = value;
        node->next = next;
    }
    return node;
}


/************************************************
 * ADDING ELEMENTS TO LIST
 ***********************************************/


/* *
 *	push:
 *
 *	DESCRIPTION:
 *		add a node to the front of the list
 *
 *	RETURN VALUE:
 *		if allocation was succesful in new_node(), push will return 1. else, 0.
 * */
int push(list_t *l, int value)
{
    node_t *node = new_node(value, l->head);
    int success = node != NULL;

    if (success) {
        l->head = node;
        l->nodes++;
    }
    return success;
}


/* *
 *	append:
 *
 *	DESCRIPTION:
 *		add a node to the end of the list
 *
 *	RETURN VALUE:
 *		if allocation was succesful in new_node(), append will return 1. else, 0.
 *
 *	MORE INFO:
 *		append requires a check to see if the list is empty. if it is, we push
 *		it to the beginning of the list. otherwise, we loop to the last node and
 *		set the next pointer of that node to the new node. 
 * */
int append(list_t *l, int value)
{
    node_t *node = new_node(value, l->head);
    int success = node != NULL;
    node_t *tmp = l->head;
    node->next = NULL;

    if (!tmp) {
        tmp = node;
		tmp->next = NULL;
	} else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = node;
    }
    l->nodes++;
    return success;
}


/************************************************
 * REMOVING ELEMENTS FROM LIST
 ***********************************************/


/* *
 *	pop:
 *
 *	DESCRIPTION:
 *		remove the last node in a list and return the value.
 *
 *	RETURN VALUE:
 *		returns the last element in the list as an int, doesn't return the node.
 *		if list is empty, -1 is returned.
 **/
int pop(list_t *l)
{
    int last = -1;
    node_t *p = l->head;
    node_t *prev = NULL;

	// empty list
	if (get_size(l) == 0)
		return last;
	else if (get_size(l) == 1) {
        last = p->value;
        l->head = NULL;
    } else {
        while (p->next) {
            prev = p;
            p = p->next;
        }
        last = p->value;
        prev->next = NULL;
    }
    free(p);
    l->nodes--;
    return last;
}


/* *
 *	shift:
 *
 *	DESCRIPTION:
 *		remove the first node in a list and return the value.
 *
 *	RETURN VALUE:
 *		returns the value in the first node in the list as an int, doesn't
 *		return the node. if list is empty, -1 is returned.
 **/
int shift(list_t *l)
{
    int first = -1;
	
	if (get_size(l) == 0)
		return first;

    node_t *tmp = l->head;
    first = tmp->value;

    l->head = tmp->next;

    free(tmp);
    l->nodes--;
    return first;
}


/* *
 *	remove_node:
 *
 *	DESCRIPTION:
 *		linearly search a list for a node containing target as its value. if
 *		found, remove that node from the list.
 *
 *	RETURN VALUE:
 *		if node with target was found 1 is returned, otherwise -1. 
 **/
int remove_node(list_t *l, int target)
{
    node_t **p = &l->head;
    node_t *tmp = NULL;

    while((*p)->next && (**p).value != target)
        p = &(*p)->next;
    if ((*p)->value == target) {
        tmp = *p;
        *p = tmp->next;
        free(tmp);
        l->nodes--;
        return 1;
    }
    return -1;
}



/************************************************
 * UTILITY FUNCTIONS
 ***********************************************/

/* *
 *	search:
 *
 *	DESCRIPTION:
 *		do a linear search for a node containing target as a value.
 *
 *	RETURN VALUE:
 *		if value is found, it returns that value, otherwise -1.
 **/
int search(list_t *l, int target)
{
    node_t **p = &l->head;
    while((*p)->next && (*p)->value != target)
        p = &(*p)->next;

    if ((*p)->value == target)
        return target;
    return -1;
}


/* *
 *	destroy_list:
 *
 *	DESCRIPTION:
 *		clean up and free entire list. no return value;
 **/
void destroy_list(list_t *l)
{
    node_t *cur = l->head;
    node_t *next = NULL;

    while (cur) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(l);
}


/* *
 *	print_list:
 *
 *	DESCRIPTION:
 *		print out the value in each node and number them. no return value;
 **/
void print_list(list_t *l)
{
    node_t *tmp = l->head;
    int i = 1;

    while (tmp) {
        printf("%d: %d\n", i++, tmp->value);
        tmp = tmp->next;
    }
}


// get_size: return the number of nodes in a list
size_t get_size(list_t *list)
{
    return list->nodes;
}



/* *
 *	reverse:
 *
 *	DESCRIPTION:
 *		reverse a linked list
 *
 *	RETURN VALUE:
 *		look great in an interview
 **/
void reverse(list_t *l)
{
    node_t *prev = NULL;
    node_t *cur = l->head;
    node_t *next = l->head;

    while (cur) {
        next = next->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    l->head = prev;
}
