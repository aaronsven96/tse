/*
 *This is an implementation of a Hashtable using a linked list
 *
 *
 *Author Aaron Svendsen
 *
 */

#include "jhash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_


/*****************global variabless***************/
typedef struct hashtable{
  int* size;
  list_t **hashtable;
  void (*itemdelete)(void *data);
} hashtable_t;

/****************global functions***************/
hashtable_t *hashtable_new(const int num_slots,void (*itemdelete)(void *data));
void *hashtable_find(hashtable_t *ht, char *key);
bool hashtable_insert(hashtable_t *ht, char *key, void *data);
void hashtable_delete(hashtable_t *ht);
void hashtable_iterate(hashtable_t *ht,
		       void (*itemfunc)(void *arg, char *key, void *data),
		       void *arg);
#endif // _HASHTABLE_H_
