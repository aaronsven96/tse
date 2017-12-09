/*
 *Head file for counters
 *
 *Author Aaron
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef _COUNTERS_H_
#define _COUNTERS_H_

/******************global types**************/
typedef struct node node_t;

typedef struct counters{

  node_t *head;
  node_t *current;

}counters_t;

/******************global functions**********/
counters_t *counters_new(void);
void counters_add(counters_t *ctrs, int key);
int counters_get(counters_t *ctrs, int key);
void counters_delete(counters_t *ctrs);
void counters_set(counters_t *ctrs, int key, int count);
void counters_iterate(counters_t *ctrs,
		      void (*itemfunc)(void *arg, int key, int count),
		      void *arg);
#endif // __COUNTERS_H
