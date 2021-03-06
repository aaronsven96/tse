/*
 *Test program for counters
 *
 *Author Aaron
 *
 */

#include <stdio.h>
#include "counters.h"

//test
void countersprint(void *arg, int key, int count);
int main(){
  counters_t* counters=counters_new();

  printf("find number of sixes: %d\n",counters_get(counters,6));
  printf("add two 5s,one 4,three 6s\n");
  //add to counters
  counters_add(counters,5);
  counters_add(counters,4);
  counters_add(counters,6);
  counters_add(counters,6);
  counters_add(counters,6);
  counters_add(counters,5);
  //find items
  printf("find number of sixes: %d\n",counters_get(counters,6));
  printf("find number of tens: %d\n",counters_get(counters,10));
  printf("find number of fives: %d\n",counters_get(counters,5));
  printf("find number of fours: %d\n",counters_get(counters,4));
  counters_iterate(counters,countersprint,NULL);
  //delete
  printf("delete");
  //counters_delete(counters);
}
void countersprint(void *arg, int key, int count){
  printf("key:%d, count:%d\n",key,count);
}
