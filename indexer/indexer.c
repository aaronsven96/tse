/*
 *Indexers that writes an index file from the crawler output 
 *
 *
 *
 *Authors Aaron Svendsen and William Wolfe
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
#include "../lib/counters/counters.h"
#include "../lib/hashtable/hashtable.h"
#include "../common/file.h"
#include "../common/word.h"


/************Function Prototypes**************/
static bool isdir(char* dir);
static void checkargs(int argc,char *argv[]);
static bool isfile(char* file);
static bool indexer(hashtable_t* ht,char*);
static void getWords(hashtable_t* ht,FILE*,int);
static void populateTable(hashtable_t* ht, char* words,int idNum);
static void delete(void *data);
static void printword(void *arg, char *key, void *data);
static void counterprint(void *arg, int key, int count);
/***************Main*************************/
int main(int argc,char *argv[]){
  checkargs(argc,argv);//checks arguments

  //Make Hashtable
  hashtable_t* ht = hashtable_new(5000,delete);

  //Reads and populates hashtable
  indexer(ht,argv[1]);

  //prints hashtable
  FILE *fp=fopen(argv[2],"ab");
  hashtable_iterate(ht,printword,fp);
  fclose(fp);

  //deletes hashtable
  hashtable_delete(ht);
  return 0;
}

//checks arguments
static void checkargs(int argc,char *argv[]){
  if(argc!=3){//checks number
    printf("Need exactly 2 arguments");
    exit(1);
  }
  if(!isdir(argv[1])){//makes sure directory
    printf("Not crawler dir");
    exit(2);
  }
  if(!isfile(argv[2])){//Makes sure it is a file
    printf("Not a writable file");
    exit(3);
  }
}

//checks to make sure has .crawler
static bool isdir(char* dir){
  char dircraw[100];
  FILE *fp;
  //Makes new string for name
  strcpy(dircraw,dir);
  strcat(dircraw,"/.crawler");
  //trys to open
  if ((fp=fopen(dircraw,"r"))==NULL){
    return false;
    fclose(fp);
  }
  fclose(fp);
  return true;
}

//makes sure it is file
static bool isfile(char* file){
  FILE *fp;
  //trys to open
  if ((fp=fopen(file,"r"))==NULL){
    //fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}

//Read though file and populates the hashtable withwords
static bool indexer(hashtable_t* ht, char* dir){
  FILE* file;
  int i = 1;//doc id
  int length = snprintf(NULL,0,"%s/%d",dir,i);//length of filename
  char* fName;

  //malloc size for filename
  if((fName = malloc(length+2)) == NULL)
    return false;
  //creating the string for filename
  if(snprintf(fName,length+1,"%s/%d",dir,i)<0)
    return false;
  //open files and reads the words
  while((file = fopen(fName,"r"))!=NULL){
    getWords(ht,file,i);//reads the words and populates table
    fclose(file);
    free(fName);
    i++;
    int length = snprintf(NULL,0,"%s/%d",dir,i);

    //creating filename with new id num
    if((fName = malloc(length+2)) == NULL)
      return false;
    if(snprintf(fName,length+1,"%s/%d",dir,i) < 0)
      return false;		
		
  }
  //frees name
  free(fName);
  return true;
}

//gets all words from the file 
static void getWords(hashtable_t* ht, FILE* file, int idNum){	
	
  //Makes file a string
  char* doc = readfile(file);

  //makes a words
  char** temp = malloc(8);
  char** words = temp; 	
  int pos = 0;

  //goes through getting everyword
  while((pos = GetNextWord(doc, pos,words))!=-1){
    populateTable(ht,*words,idNum);//adds word to hashtable
  }
  //frees doc and temp
  free(doc);
  free(temp);
}

//populates the table with a word
static void populateTable(hashtable_t* ht, char* words,int idNum){
  words = NormalizeWord(words);//Normalizes

  //checks length
  if (strlen(words)<=2){
    free(words);
    return;
  }

  //Makes new counter with info
  counters_t* tempCounter = counters_new();
  counters_add(tempCounter,idNum);

  //trys to insert
  if(!hashtable_insert(ht,words,tempCounter)){

    //if insert fails then delete the temp and increment in hashtable
    counters_delete(tempCounter);
    counters_add((counters_t*)hashtable_find(ht,words),idNum);
    free(words);
  }
}

//function thats deletes a counters object
static void delete(void *data){
  counters_t *ctrs=data;
  counters_delete(ctrs);
}

//prints key to file 
static void printword(void *arg, char *key, void *data){
  FILE *fp=arg;
  if (fp!=NULL){
    fputs(key,fp);
  }

  //calls counter iterate on the data
  counters_t *count=data;
  counters_iterate(count,counterprint,fp);

  fputs("\n",fp);//prints new line
}

//prints data in counter
static void counterprint(void *arg, int key, int count){
  FILE *fp=arg;
  if (fp!=NULL){
    fprintf(fp," %d", key);
    fprintf(fp," %d", count);
  }
}
