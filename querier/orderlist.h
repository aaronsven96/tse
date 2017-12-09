/*
 *Header File for list 
 *
 *Author: William Wolfe by the way Aaron Svendsen sucks
 *
 */
#include <stdbool.h>
#include "../lib/hashtable/hashtable.h"
#include "../lib/counters/counters.h"

#ifndef _ORDERLIST_H_
#define _ORDERLIST_H_
/***********************local types*************/
typedef struct node node;
/***********************global types************/
typedef struct orderlist{
  node*head;
  void (*itemdelete)(void *data);
} orderlist_t;
/**********************global functions*********/
orderlist_t *orderlist_new(void (*itemdelete)(void *data),hashtable_t* ht,char*word);
orderlist_t* orderlist_and(orderlist_t* ls, hashtable_t* ht, char* word);
void orderlist_or(orderlist_t* right, orderlist_t* left);
void orderlist_delete(orderlist_t *list);
void orderlist_iterate(orderlist_t *ordls,
		       void (*itemfunc)(void *arg, int key, int count),
		       void *arg);
#endif // __ORDERLIST_H
