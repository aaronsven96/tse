/*
 *implementation of a Linked List 
 *
 *Author: Aaron Svendsen
 *
 */
#include"list.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
/***********************local types*************/
typedef struct node{
  struct node *next;
  void* data;
  char* key;
}node;
/***********************global types************/
//In .h file
/**********************global functions*********/

//make new list
list_t *list_new(void (*itemdelete)(void *data)){
  list_t* newlist=malloc(sizeof(list_t));
  node* newnode=malloc(sizeof(node));
  newlist->itemdelete=itemdelete;
  newlist->head=newnode;
  newlist->current=newnode;
  newnode->next=NULL;
  return newlist;

}

void *list_find(list_t *list, char *key){ 
  //if list doesn't exist
  if (list==NULL){
    return NULL;
  }
  node *find;//node that finds 
  find=(node*)list->head->next;
  //goes thorugh list and returns data
  while(find!=NULL){
    if (strcmp(find->key,key)==0){
      return find->data;
    }
    find=find->next;
  }
  return NULL;
}

//insert new node
bool list_insert(list_t *list,char *key, void *data){
  //checks to see if it is already there
  if (list_find(list,key)!=NULL){
    return false;
  }
  //must be a list
  else if (list==NULL){
    return false;
  }
  //makes new node and allocate memory
  else{
    node* newnode=malloc(sizeof(node));
    newnode->data=data;
    newnode->key=key;
    list->current->next=newnode;
    list->current=newnode;
    newnode->next=NULL;
    return true;
  }
}
void list_delete(list_t *list){
  node *find=list->head;
  node *toremove=find;
  while(find->next!=NULL){
    toremove=find;
    find=find->next;
    if (list->itemdelete!=NULL){
      list->itemdelete(toremove->data);
    }
    free(toremove);
  }
  if (list->itemdelete!=NULL){
    list->itemdelete(find->data);
  }
  free(find);
  free(list);
}

