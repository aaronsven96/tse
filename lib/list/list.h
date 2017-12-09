/*
 *Header File for list 
 *
 *Author: Aaron Svendsen
 *
 */
#include<stdbool.h>
#ifndef _LIST_H_
#define _LIST_H_
/***********************local types*************/
typedef struct node node;
/***********************global types************/
typedef struct sll{
  node*head;
  node*current;
  void (*itemdelete)(void *data);
} list_t;
/**********************global functions*********/
list_t *list_new(void (*itemdelete)(void *data));
void *list_find(list_t* list, char *key);
bool list_insert(list_t *list,char *key, void *data);
void list_delete(list_t *list);

#endif // __LIST_H
