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
#include "hashtable.h"

/*****************global variabless***************/
//in .h file
/****************global functions***************/

//makes new hash table
hashtable_t *hashtable_new(const int num_slots,void (*itemdelete)(void *data)){
  printf("New Table");
  hashtable_t *newtable=malloc(sizeof(hashtable_t));
  list_t **hashtable=malloc(num_slots*sizeof(list_t));
  newtable->itemdelete=itemdelete;
  newtable->size=malloc(sizeof(int));
  *newtable->size=num_slots;
  newtable->hashtable=hashtable;
  for(int i=0;i<num_slots;i++){
    newtable->hashtable[i]=NULL;
  }
  return newtable;
}

bool hashtable_insert(hashtable_t *ht, char *key, void *data){
  //see if key is already used
  if (hashtable_find(ht,key)!=NULL){
    return false;
  }
  else{
    //finds hash code
    int code=JenkinsHash(key,*ht->size);
    if (ht->hashtable[code]==NULL){
      ht->hashtable[code]=list_new(ht->itemdelete);
    }
    //inserts
    if (list_insert(ht->hashtable[code],key,data)){
      return true;
    }		  
    else {
      return false;
    }
  }
}

//finds data at key
void *hashtable_find(hashtable_t *ht, char *key){
  int code=JenkinsHash(key,*ht->size);
  if(ht->hashtable[code]==NULL){
    return NULL;
  }
  return list_find(ht->hashtable[code],key);
}

//deletes table
void hashtable_delete(hashtable_t *ht){
  //goes through table and deletes lists
  for(int i=*ht->size-1;i>=0;i--){
    if(ht->hashtable[i]!=NULL){
      list_delete(ht->hashtable[i]);
      
      }
  }
  free(ht->hashtable);
  free(ht->size);
  free(ht);
}
void hashtable_iterate(hashtable_t *ht,
		       void (*itemfunc)(void *arg, char *key, void *data),
		       void *arg){
  for(int i=*ht->size-1;i>=0;i--){
    if(ht->hashtable[i]!=NULL){
      list_iterate(ht->hashtable[i],itemfunc,arg);
    }
  }
}
