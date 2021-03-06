/*
 *Counter data structure that uses key and amount
 *
 *Author Aaron
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"

/******************global types**************/
//in .h file
/******************local types***************/
typedef struct node{
  int *key;
  int *num;
  struct node* next;
  
}node_t;


/******************global functions**********/

//makes new counter
counters_t *counters_new(void){
  counters_t *counters=malloc(sizeof(counters_t));
  node_t *node=malloc(sizeof(node_t));
  node->next=NULL;
  counters->head=node;
  counters->current=node;
  return counters;
}

int counters_get(counters_t *ctrs, int key){
  node_t *find=ctrs->head->next;//head
  //goes through whole list
  while(find!=NULL){ 
    if (*find->key==key){
      return *find->num;
    }
    find=find->next;
  }
  return 0;
}

// adds new counter and increments existing counter
void counters_add(counters_t *ctrs, int key){
  if (ctrs!=NULL){
    node_t *find=ctrs->head->next;
    bool add=true;
    //find and increment
    while(find!=NULL){
      if (*find->key==key){
	*find->num+=1;
	add=false;
      }
      find=find->next;
    }
    //if not found then add
    if (add){
      node_t *node=malloc(sizeof(node_t));
      node->key=malloc(sizeof(int));
      node->num=malloc(sizeof(int));    
      node->next=NULL;
      *node->key=key;
      *node->num=1;
      ctrs->current->next=node;
      ctrs->current=node;
    }
  }
}

//deletes counters
void counters_delete(counters_t *ctrs){
  node_t *find=ctrs->head->next;
  node_t *toremove=find;
  //deletsnodes 
  while(find!=NULL){
    find=find->next;
    free(toremove->num);
    free(toremove->key);
    free(toremove);
    toremove=find;
  }
  //deletes find
  free(ctrs->head);
  free(ctrs);
}

//sets counter value
void counters_set(counters_t *ctrs, int key, int count){
  if (ctrs!=NULL){
    node_t *find=ctrs->head->next;
    bool add=true;
    //find and increment
    while(find!=NULL){
      if (*find->key==key){
	*find->num=count;
	add=false;
      }
      find=find->next;
    }
    //if not found then add
    if (add){
      node_t *node=malloc(sizeof(node_t));
      node->key=malloc(sizeof(int));
      node->num=malloc(sizeof(int));
      node->next=NULL;
      *node->key=key;
      *node->num=1;
      ctrs->current->next=node;
      ctrs->current=node;
    }
  }
}
void counters_iterate(counters_t *ctrs,
		      void (*itemfunc)(void *arg, int key, int count),
		      void *arg){
  if(ctrs==NULL || itemfunc==NULL){
    return;
  }
  node_t *find=ctrs->head->next;//head
  //goes through whole list
  while(find!=NULL){ 
    (*itemfunc)(arg,*find->key,*find->num);
    find=find->next;
  }
}
