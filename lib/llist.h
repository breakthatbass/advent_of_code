/******************************************************************************
*
*   Author: Taylor Gamache
*   Email: gamache.taylor@gmail.com
*
*   Version: 0.1.2
*
*   License: MIT 2020
*
******************************************************************************/


#ifndef LLIST_H__
#define LLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};
typedef struct node node_t;

struct list {
    node_t *head;
    size_t nodes;
};
typedef struct list list_t;


// LINKED LIST API

//void list_init(list_t *list);
list_t *list_init(void);

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
int push(list_t *l, int value);


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
int append(list_t *l, int value);


 /************************************************
 * REMOVING ELEMENTS FROM LIST
 ************************************************/


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
int pop(list_t *l);


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
int shift(list_t *l);


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
int remove_node(list_t *l, int target);


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
int search(list_t *l, int target);


/* *
 *	destroy_list:
 *
 *	DESCRIPTION:
 *		clean up and free entire list. no return value;
 **/
void destroy_list(list_t *l);


/* *
 *	print_list:
 *
 *	DESCRIPTION:
 *		print out the value in each node and number them. no return value;
 **/
void print_list(list_t *l);


// get_size: return the number of nodes in a list
size_t get_size(list_t *list);


/* *
 *	reverse:
 *
 *	DESCRIPTION:
 *		reverse a linked list
 *
 *	RETURN VALUE:
 *		look great in an interview
 **/
void reverse(list_t *l);


#ifdef __cplusplus
}
#endif // extern "C"

#endif // __LLIST_H__
