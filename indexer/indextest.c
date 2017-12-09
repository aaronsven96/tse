/*
 *takes info from input file, populates info from file into hashtable and puts it in 
 *ouput file from the crawler output 
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
static void checkargs(int argc,char *argv[]);
static bool isfile(char* file);
static void getWords(hashtable_t* ht,FILE*);
static void populateTable(hashtable_t* ht, char* words,int idNum,int numOccur);
static void delete(void *data);
static void printword(void *arg, char *key, void *data);
static void counterprint(void *arg, int key, int count);
/***************Main*************************/
int main(int argc,char *argv[]){

  checkargs(argc,argv);//check to see if arguments are correct

  hashtable_t* ht = hashtable_new(512,delete);//create a new hashtable with given delete function

  FILE* in;
  in = fopen(argv[1],"r");//open input file from arguments
  getWords(ht,in);//process file
  FILE* out = fopen(argv[2],"w+");//open output file from arguments
  hashtable_iterate(ht,printword,out); //iterate through hashtable and save table to output file
  fclose(in);
  fclose(out);
  hashtable_delete(ht);//delete file

  return 0;
}



//checks arguments
static void checkargs(int argc,char *argv[]){
  if(argc!=3){
    printf("Need exactly 2 arguments");
    exit(1);
  }

  if(!isfile(argv[1])){
    printf("Not a writable file");
    exit(3);
  }
}

//makes sure it is file
static bool isfile(char* file){
  FILE *fp;
  if ((fp=fopen(file,"r"))==NULL){
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}

//process file putting found words into hashtable
static void getWords(hashtable_t* ht, FILE* file){



  char* word;//string extracted from file to be precessed
  char* wordT;//word to insert into table
  int idNum;
  int numOccur;

  //if the word is null then the file is ended
  while((word = readword(file)) != NULL){
    //if the word is a word and not a number
    if((isdigit(*word))==0){
      //store the word into the offical word
      wordT = word;
      //get the idnum which should be next word
      if((word = readword(file)) == NULL)
	break;
      //turn word into in for idnum
      idNum = atoi(word);
      //free the word
      free(word);
      //get the numOccur which should be next word
      if((word = readword(file)) == NULL)
	break;
      //turn word into in for numOccur
      numOccur = atoi(word);
      free(word);

      //else the word is an idNum
    }else{
      //turn word into in for idnum
      idNum = atoi(word);
      free(word);
      //get the numOccur which should be next word
      if((word = readword(file)) == NULL)
	break;
      //turn word into in for numOccur
      numOccur = atoi(word);
      free(word);
    }
    //populate the table with the new wordT, idnum, and numoccur
    populateTable(ht, wordT, idNum, numOccur);


  }
  free(word);



}



//populate the hashtable with the given arguments
static void populateTable(hashtable_t* ht, char* words,int idNum,int numOccur){

  counters_t* tempCounter = counters_new();//create a new counter
  counters_add(tempCounter,idNum);//populate th enew counter with the id of the page
  counters_set(tempCounter,idNum,numOccur);//set the counter at the id wiht the correct number of occurences of that word
  if(!hashtable_insert(ht,words,tempCounter)){//if the word is already in the hashtable
    counters_delete(tempCounter);//free the counter
    counters_add((counters_t*)hashtable_find(ht,words),idNum);//add the idnum
    counters_set((counters_t*)hashtable_find(ht,words),idNum,numOccur);//set the node at idnum with the given numoccur
  }
}

//delete a counter
static void delete(void *data){
  counters_t *ctrs=data;
  counters_delete(ctrs);
}

//print a word in counter
static void printword(void *arg, char *key, void *data){
  FILE *fp=arg;
  if (fp!=NULL){
    fputs(key,fp);
  }
  counters_t *count=data;
  counters_iterate(count,counterprint,fp);
  fputs("\n",fp);
}

//print a word in counter
static void counterprint(void *arg, int key, int count){
  FILE *fp=arg;
  if (fp!=NULL){
    fprintf(fp," %d", key);
    fprintf(fp," %d", count);
  }
}


