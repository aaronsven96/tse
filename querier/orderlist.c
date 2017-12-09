/*
 *implementation of a Ordered List 
 *
 *Author: Aaron Svendsen and William Wolfe
 *
 */
#include "orderlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include "../lib/hashtable/hashtable.h"
//#include "../lib/counters/counters.h"
/***********************local types*************/
typedef struct node{
  struct node *next;
  int score;
  int idnum;
  //char* word;
  bool mark;
}node;
/********************local functions*************/
static orderlist_t* newHelper(orderlist_t*,hashtable_t* , char*);
static void addToList(void* , int , int );
static void andHelper(void* , int , int );
static void insert(orderlist_t* ,node* );
static node* copy(node* );
/***********************global types************/
//In .h file
/**********************global functions*********/

/*void orderlist_and(orderlist_t* , hashtable_t*, char* );
void orderlist_or(orderlist_t* , orderlist_t* );
orderlist_t* list_new(void (*itemdelete)(void *data),hashtable_t* ht,char* word){*/

//make new list
orderlist_t * orderlist_new(void (*itemdelete)(void *data),hashtable_t* ht,char* word){

  //create new order list with null head
  orderlist_t* newlist=malloc(sizeof(orderlist_t));
  newlist->itemdelete=itemdelete;
  newlist->head=NULL;

  //populate the list with the given word from the hashtable
  newlist = newHelper(newlist, ht, word);
  return newlist;

}

static node* copy(node* in){
  node* outNode = malloc(sizeof(node));
  outNode->score = in->score;
  outNode->idnum = in->idnum;
  outNode->mark = in->mark;
  outNode->next = in->next;
  return outNode;
}

static orderlist_t* newHelper(orderlist_t* ls, hashtable_t* ht, char* word){

  counters_t* ct;

  //if the word is not in the hashtable, delete the list and end the function
  if((ct = (counters_t*)hashtable_find(ht,word))==NULL){
    orderlist_delete(ls);
    // ls = NULL;
    return NULL;
  }

  //call the iterator on the counter and use addToList as function
  counters_iterate(ct, addToList,ls);
  return ls;
}

//may not need word
static void addToList(void* ls1, int idnum, int numoccur){
  orderlist_t* ls = ls1;
  //make a new temp node out of the given data
  node* temp = malloc(sizeof(node));
  temp->next = NULL;
  temp->score=numoccur;
  temp->idnum=idnum;
  temp->mark = false;
  //temp->word = malloc(strln(word));
  //stpcpy(temp->word,word);
  //if the head in empty then set the temp node to the head and end the function
  if(ls->head == NULL){
    ls->head = temp;
    return;
  }

  //insert back into list to maintain order
  insert(ls,temp);

}

orderlist_t*  orderlist_and(orderlist_t* ls, hashtable_t* ht, char* word){

  //if the list is null then end the function
  if(ls==NULL){
    //printf("list is null, ending and function\n");
    ls = NULL;
    return ls;
  }

  //if there is no word in the hashtable then the list can be deleted as the and statment
  //cannot be completed
  counters_t* ct;
  if((ct = (counters_t*)hashtable_find(ht,word))==NULL){
    //printf("word is not in the list, making list null\n");
    orderlist_delete(ls);
    ls = NULL;
    return ls;
  }


  //call iterator on counter and run andhelper
  counters_iterate(ct, andHelper,ls);
  //iterate through the orderlist removing any non tagged nodes(non taged means
  //both words are not in the doc thus the node with the corisponding doc should be removed)
  node* prev=NULL;
  node* iter = ls->head;
  while(iter!=NULL){

    //if the node is not marked
    if(!iter->mark){
      //delete the mode, treat head differently
      if(iter==ls->head){
	ls->head = iter->next;
	//may be blank, may also need to free mark and next
	//free(iter->word);
	free(iter);
	iter = ls->head;
	continue;
      }else{
	prev->next = iter->next;
	//may be blank, may also need to free mark and next
	//free(iter->word);
	free(iter);
	iter = prev;
      }
      //else if the node is marked, de mrk for next and operation
    }else{
      iter->mark = false;
    }

    prev = iter;
    iter=iter->next;
  }

  //if the head is now null (no docs satisfied the and operation) make the list null
  if(ls->head==NULL)
    ls = NULL;
  
  return ls;
}

static void andHelper(void* ls1, int idnum, int numoccur){
  orderlist_t* ls = ls1;

  //loop through the orderlist and find the node with the corispongind idnum
  node* prev=NULL;
  node* iter = ls->head;
  while(iter!=NULL){
    //find the node with the corisponding idnum
    if(idnum == iter->idnum){
      iter->mark = true;
      if(iter == ls->head){
	//if the number of occurences for the new word is less than the previous word
	//then set the score to the number of occurences of the new word
	if(numoccur < iter->score){
	  iter->score = numoccur;
	  //remove the node from the list
	  ls->head = iter->next;
	  iter->next = NULL;
	  //insert the node back into the list in the apropriate order
	  insert(ls,copy(iter));
	  //iter = prev;
	  iter = ls->head;
	  continue;
	}
      }else{
	//if the number of occurences for the new word is less than the previous word
	//then set the score to the number of occurences of the new word
	if(numoccur < iter->score){
	  iter->score = numoccur;
	  //remove the node from the list
	  prev->next = iter->next;
	  iter->next = NULL;
	  //insert the node back into the list in the apropriate order
	  insert(ls,copy(iter));
	  iter = prev;
	}
      }
    }
    
    prev = iter;
    //printf("id:%d, score: %d\n ",iter->idnum,iter->score);
    //printf("%s",iter->next);
    if (iter==NULL){
	  break;
    }
    iter=iter->next;
  }

}

//combine rightlist into left orderlist, right orderlist will be deleted
void orderlist_or(orderlist_t* left, orderlist_t* right){
  
  //iterate through left orderlist comparing idnums to right orderlist
  //node* prevL=NULL;
  node* iterL = left->head;
  while(iterL!=NULL){

    //iterate through right list to compareing all nodes in right list to the current left orderlist node
    //node* prevR=NULL;
    node* iterR = right->head;
    while(iterR!=NULL){

      //if the idnums of both items are the same
      if(iterL->idnum == iterR->idnum){
	iterL->score = iterL->score + iterR->score; // add the scores into left orderlist node
	iterR->idnum = -1;
      }

      //prevR = iterR;
      iterR = iterR->next;
    }

    //prevL = iterL;
    iterL=iterL->next;
  }

  //loop through the remaining items in the right order list and add the items that have
  //not already been added into the left order list
  node* iterR = right->head;
  while(iterR!=NULL){

    //if the idnum is -1 then the node as already been added to the left orderlist
    if(iterR->idnum != -1){
      node* temp = iterR->next;
      iterR->next = NULL;
      insert(left,copy(iterR));
  //    free(iterR);
      iterR = temp;
      continue;
    }
    //node* temp2 = iterR;
    iterR = iterR->next;
    //free(temp2);
  }

  orderlist_delete(right);
  //insert remaining items from left to right
}

static void insert(orderlist_t* ls,node* temp){
  //make a previous node and an iterator node, then move through the items in the list
  node* prev=NULL;
 // printf("if head is null then prev can be null but ls should never be null. ls head:%s ",ls->head);
  if(ls->head == NULL){
	ls->head = temp;
        return;
  }
  node* iter = ls->head;
  while(iter!=NULL){

    //if the score of the temp node is greater than equal to the current
    //node insert the temp node before the iterator node
    if(temp->score >= iter->score ){
      //if the iterator node is the head then insert the temp node at
      //the head and shift the list down.
      //else insert the temp node between previous node and iterator node
      if(ls->head == iter){
	temp->next = iter;
	ls->head = temp;
	break;
      }else{
	temp->next=iter;
	prev->next=temp;
	break;
      }

    }

    //move on to next node
    prev = iter;
    iter=iter->next;
  }
  //if the temp node has no next then it has not been inserted into the list
  //thus the score is the smallest and should be put at the end
  if(temp->next == NULL){
     prev->next = temp;
  }

}

void orderlist_delete(orderlist_t* ls){
  if(ls==NULL)
	return;
  node *find=ls->head;
  node *toremove=find;
  //deletsnodes
  while(find!=NULL){
    find=find->next;
    //free(toremove->idnum);
    //free(toremove->score);
    free(toremove);
    toremove=find;
  }
  //frees orderlist
  free(ls);
}

void orderlist_iterate(orderlist_t *ordls,
		      void (*itemfunc)(void *arg, int key, int count),
		      void *arg){
  if(ordls==NULL || itemfunc==NULL){
    return;
  }
  node *find=ordls->head;//head
  //goes through whole list
  while(find!=NULL){
    (*itemfunc)(arg,find->idnum,find->score);
    find=find->next;
  }
}
