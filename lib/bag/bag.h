/* 
 *Header file for bag.c
 *
 *Aaron Svendsen
 *
 */

#include <stdio.h>
#include <stdlib.h>


/*****************local variable***************/
typedef struct sllist sllist_t;


/******************global types****************/
typedef struct bag{
  sllist_t *current;
  sllist_t *head;
  void (*itemdelete)(void *data);
}bag_t;


/*******************global functions*********/
bag_t *bag_new(void (*itemdelete)(void *data));
void bag_insert(bag_t *bag, void *data);
void *bag_extract(bag_t *bag);
void bag_delete(bag_t *bag);
