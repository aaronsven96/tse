/*
 *Code for crawler that take a starter Url and and crawls through webpages 
 *to a certian depth, and stores htnl data in a folder
 *
 *Authors: Aaron Svendsen, William Wolfe
 *
 *
 */

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../common/web.h"
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../lib/bag/bag.h"
#include "../lib/hashtable/hashtable.h"

/************Global Variables****************/
static int idNum = 0;
static int maxdepth = 10;

/************Function Prototypes**************/
static bool isint(char *num);
static bool isdir(char* dir);
static bool pagesaver(WebPage*, char*);
static void crawl(WebPage* basepage,bag_t* bag,hashtable_t* ht);
static void deletepage(WebPage *page);
static bool checkargs(int argc,char *argv[]);
/***************Main*************************/

int main(int argc,char *argv[]){

  //Checks Arguments
  if(!checkargs(argc,argv)) return 1;
  
  //max depth 
  maxdepth=atoi(argv[3]);

  //init data structures
  bag_t *bag=bag_new(NULL);
  hashtable_t *table=hashtable_new(300,(*free));

  //Makes First Page
  WebPage *base=malloc(sizeof(WebPage));
  base->url=argv[1];
  base->depth=0;
  //checks and fills with html
  if (!GetWebPage(base)){
    return 2;
  }
  bag_insert(bag,base);

  //loop through bag removing an item, saving the item, and calling crawl on the
  //item to populate the bag
  WebPage *page;
  while ((page=bag_extract(bag))!=NULL){
    pagesaver(page,argv[2]);
    printf("printing:%s\n",page->url);
    crawl(page,bag,table);
    deletepage(page);
    }
  bag_delete(bag);
  hashtable_delete(table);
  return 0;
}

//Checks to see if input is int
static bool isint(char *num){
  while(*num!='\0'){
    if (isdigit(*num)!=0){
      num++;
    }
    else {
      return false;
    }
  }
  return true;
}

//checks to see if input is directory
static bool isdir(char* dir){
  FILE *fp;
  char str[80];
  strcpy(str,dir);
  strcat(str,"/.crawler");
  if ((fp=fopen(str, "w"))==NULL){
    fclose(fp);
    return false;
  }
  fclose(fp);
  struct stat statbuf;
  if (stat(dir,&statbuf)!=0){
    return false;
  }
  if (S_ISDIR(statbuf.st_mode)!=0){
    return true;
  }
    return false;
}

//returns true if page sucsessfuly added to file, otherwise returns false
static bool pagesaver(WebPage* page,char* dir){
  idNum++;

  //malloc correct file name and check to make sure the name and size are valid
  int length = snprintf(NULL,0,"%s/%d",dir,idNum);
  char* fName;
  if((fName = malloc(length+1)) == NULL)
    return false;
  if(snprintf(fName,length+1,"%s/%d",dir,idNum)<0)
    return false;

  //create the file and store the apropirate data
  FILE* file;
  if((file = fopen(fName,"w+")) == NULL)
    return false;
  fprintf(file,"%s\n",page->url);
  fprintf(file,"%d\n",page->depth);
  fprintf(file,"%s\n",page->html);
  fclose(file);
  printf("file closes\n");
  free(fName);

  return true;
}

//find all the valid URLs in the given web page and store them in bag
static void crawl(WebPage* basepage,bag_t* bag,hashtable_t* ht){
  if(basepage->depth >= maxdepth)
    return;
  int pos = 0;
  char* result=NULL;
  while((pos = GetNextURL(basepage->html,pos,basepage->url,&result))>0){
    //sleep(1);

    //check result with NormalizeURL and IsInternalURL
    //continue if url is not valid
    if(!NormalizeURL(result) || !IsInternalURL(result)){
      free(result);
      continue;
    }
    
    //Try to insert the url into a hashtable of urls.
    //If the insert fails then the url has already ben visited
    //and the loop continues.
    char *cpy=malloc(strlen(result)+1);
    strcpy(cpy,result);
    printf("Copy:%s\n",cpy);
    if(!hashtable_insert(ht,cpy,cpy)){
      free(result);
      free(cpy);
      continue;
    }
    
    //create a new WebPage module from the url
    WebPage* temp = malloc(sizeof(WebPage));
    temp->url = cpy;
    temp->depth = basepage->depth + 1;

    //if no webpage can be recived
    //free the temp webpage object and continue
    if(!GetWebPage(temp)){
      //free(temp->url);
      free(temp->html);
      free(temp);
      free(result);
      continue;
    }
    
    //add WebPage module to bag
    bag_insert(bag,temp);
    free(result);
  }
}

//free the given webpage
static void deletepage(WebPage *page){
  free(page->html);
  free(page);
}


//check the inserted arguments
static bool checkargs(int argc,char* argv[]){
  if (argc!=4){
    printf("Need exactly 3 arguments");
    return false;
  }
  if (!NormalizeURL(argv[1])||!IsInternalURL(argv[1])){
    printf("Url must be correct and within cs50 pages");
    return false;
  }
  if (!isint(argv[3])&&atoi(argv[3])<maxdepth){
    printf("Third Argument must be number between zero and 10");
    return false;
  }   
  if (!isdir(argv[2])){
    printf("Second Argument must be a directory");
    return false;
  }
  return true;
}
