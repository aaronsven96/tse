
/* 
 *Test code for Bag
 *
 *Aaron Svendsen
 *
 */
#include "bag.h"
#include <stdio.h>
#inlcude "../../web.h"

//Test Code
int main(){
  bag_t* bag =bag_new(NULL);
  WebPage newpage=malloc(sizeof(WebPage));
  newpage->url=malloc(sizeof());
  
  printf("Try extracting nothing %s\n",(char *)bag_extract(bag));//try extracting item not in bag
  bag_insert(bag,"data1");
  //extract twice
  printf("\nExtracts data: %s\n",(char *)bag_extract(bag));
  printf("Extracts nothing: %s\n",(char *)bag_extract(bag));
  //inserts
  bag_insert(bag,"data2");
  bag_insert(bag,"data3");
  bag_insert(bag,"data4");
  //extracts
  printf("\nInsert bunch of items and extract them\n");
  
  printf("%s ",(char *)bag_extract(bag));
  printf("%s ",(char *)bag_extract(bag));
  printf("%s ",(char *)bag_extract(bag));
  printf("%s ",(char *)bag_extract(bag));
  printf("%s ",(char *)bag_extract(bag));
  
  //deletes bag
  bag_delete(bag);
  
  return 0;
}
static void deletepage(WebPage *page){
  free(page->url);
  free(page->html);
  free(page);
}
