/*
 * Test c code for List
 *
 * Author Aaron
 *
 */
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
  list_t *new=list_new(NULL);
  list_insert(new,"dog","dog");
  printf ("Inserts item twice %s\n",list_insert(new,"dog","dog")?"true":"false");
  printf("Insert and find %s\n",(char *)list_find(new, "dog"));
  list_insert(new,"cat","cat");
  list_insert(new,"moose","moose");
  printf("Insert and find %s\n",(char *)list_find(new, "cat"));
  printf("Insert and find %s\n",(char *)list_find(new, "moose"));
  printf("Looks for item not there %s\n",(char *)list_find(new, "home"));
  list_delete(new);
}  
