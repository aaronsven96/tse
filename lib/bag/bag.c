/* 
 * This code makes a bag data structure with no order
 *
 *Aaron Svendsen
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "bag.h"
#include <stdbool.h>

/******************local types****************/
typedef struct sllist{
  struct sllist *next;
  void *data;
}sllist_t;

/******************global types****************/
//refer to bag.h
/*******************global functions*********/

//makes a new bag
bag_t *bag_new(void (*itemdelete)(void *data)){
  bag_t *bag=malloc(sizeof(bag_t));
  sllist_t *start=malloc(sizeof(sllist_t));
  
  //head and current are the same for only one item
  bag->head=start;
  bag->current=start;
  bag->itemdelete=itemdelete;
  start->next=NULL;
  return bag;
}

//inserts new data as a node
void bag_insert(bag_t *bag, void *data){
  sllist_t *item=malloc(sizeof(sllist_t));
  item->data=data;
  //moves current to new item
  bag->current->next=item;
  bag->current=item;
  item->next=NULL;
}

//removes data from bag
void *bag_extract(bag_t *bag){
  //if no items then return null
  if (bag->head->next==NULL){
    return NULL;
  }
  else{
    //data to remove
    void* toremove=bag->head->next->data;
    if (bag->head->next==bag->current){
      bag->current=bag->head;
    }
    //have to get rid of data after
    
    sllist_t *tofree=bag->head->next;
    bag->head->next=bag->head->next->next;
    //frees node
    free(tofree);
    return toremove;
  }
}

//deletes bag
void bag_delete(bag_t *bag){
  while (bag->head->next!=NULL){
    if (bag->itemdelete==NULL){//extracts
      bag_extract(bag);
    }
    else{//if delete function use that
      bag->itemdelete(bag_extract(bag));
    }
  }
  free(bag->head);
  free(bag);
}

void bag_iterate(bag_t *bag,
		 void (*itemfunc)(void *arg, void *data),
		 void *arg){
  if(bag==NULL || itemfunc==NULL){
    return;
  }
  sllist_t *find=bag->head->next;//head
  //goes through whole list
  while(find!=NULL){
    (*itemfunc)(arg,find->data);
    find=find->next;
  }
}
