/*
 *Test file for hashtable
 *
 *Author Aaron Svendsen, 4/23/16
 *
 */

#include "jhash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "hashtable.h"

int main(){
  //make table
  hashtable_t *newtable=hashtable_new(50,NULL);
  //Insering
  printf("These should be true \n");
  printf("%s\nInsert HI ",hashtable_insert(newtable,"HI","HI")? "true " : "false ");
  printf("%s\nInsert DOG ",hashtable_insert(newtable,"DOG","DOG")? "true " : "false ");
  printf("%s\nInsert CAT ",hashtable_insert(newtable,"CAT","CAT")? "true " : "false ");
  printf("%s\nInsert BYE ",hashtable_insert(newtable,"BYE","BYE")? "true " : "false ");
  printf("\n this should be false since inserting HI agian: ");
  printf("%s\nInsert HI ",hashtable_insert(newtable,"HI","HI")? "true" : "false");
  printf("%s\nInsert http://old-www.cs.dartmouth.edu/~cs50/ ",hashtable_insert(newtable,"http://old-www.cs.dartmouth.edu/~cs50/","http://old-www.cs.dartmouth.edu/~cs50/")? "true" : "false");
  printf("%s\nInsert http://old-www.cs.dartmouth.edu/~cs50/ ",hashtable_insert(newtable,"http://old-www.cs.dartmouth.edu/~cs50/","http://old-www.cs.dartmouth.edu/~cs50/")? "true" : "false");

  printf("\nFinding what we just added\n");
  //find
  printf("%s\n",(char *)hashtable_find(newtable,"HI"));
  printf("%s\n",(char *)hashtable_find(newtable,"CAT"));
  printf("%s\n",(char *)hashtable_find(newtable,"DOG"));
  printf("%s\n",(char *)hashtable_find(newtable,"BYE"));
  hashtable_delete(newtable);
  return 0;
}
