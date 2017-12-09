/*
 *Code for the querier which find urls from a query
 *Uses and and or syntax
 *
 *
 * 
 *Author Aaron Svendsen and William Wolfe
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
#include "orderlist.h"

/*********************global variable*********************/
const char *and="and";
const char *or="or";
const char space[10]=" ";
const char maxwrd=6;

/*********************function prototypes*****************/
static void checkarg(int argc,char *argv[]);
static bool isdir(char* dir);
static char *checksyntax(char* line,char *format); 
static void mklower(char *line);
static bool checkemp(char *line);
static void addor(char *line,hashtable_t *index,char *dir);
static void populateTable(hashtable_t* ht, char* words,int idNum,int numOccur);
static void getWords(hashtable_t* ht, FILE* file);
static void delete(void*data);
static void lsprint(void *arg, int idnum, int score);
static char *geturl(int idnum, char* dir);

/*****************************Main**********************/
int main(int argc,char *argv[]){
  checkarg(argc,argv);//checks args
  FILE *fp=fopen(argv[2],"r");
  hashtable_t *index=hashtable_new(1024,delete);
  getWords(index,fp);//get words for index file
  //hashtable_iterate(index,printword,stdout);
  fclose(fp);
  printf("\n");
  bool query=true;
  char *line;
  char* word;
  //main loop that accepts queriers
  while(query&&(line=readline(stdin))!=NULL){
    char *format=calloc(2,strlen(line)+1);
    word=checksyntax(line,format);//checks syntax
    if (word!=NULL){
      printf("Query: %s\n",word);
      addor(word,index,argv[1]);
      printf("----------------------------------------\n");
    }
    free(format);
    free(line);
  }
  hashtable_delete(index);
  free(line);
  return 0;
}

//check arguments and exit if incorrect
static void checkarg(int argc,char *argv[]){
  if (argc!=3){
    printf("There should be only 2 arguments\n");
    exit(1);
  }
  if(!isdir(argv[1])){
    printf("Directry must be from crawler output\n");
    exit(2);
  }
  FILE *fp;
  if ((fp=fopen(argv[2],"r"))==NULL){
    printf("Index File must be a readable file\n");
    exit(3);
  }
  fclose(fp);
}

//checks directory
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

//checks syntax of input word and returns formatting string
static char *checksyntax(char* line,char *format){
  int numwrd=0;
  if (line==NULL){
    return NULL;
  }
  if(checkemp(line)){
    return NULL;
  }
  mklower(line);
  bool wrgandor=true;
  char *word;
  word=strtok(line,space);
  while(word!=NULL){
    if (strcmp(word,and)==0||strcmp(word,or)==0){
      if (strcmp(word,or)==0){
	strcat(format,word);
	strcat(format," ");
      }
      if(wrgandor){
	printf("Error: And/or is in the wrong place\n");
	return NULL;
      }
      wrgandor=true;
    }
    else{
      numwrd++;
      strcat(format,word);
      strcat(format," ");
      wrgandor=false;
      while(*word!='\0'){
	if(!isalpha(*word)){
	  printf("Error: %c is not in the aplabet\n",*word);
	  return NULL;
	}
	word++;
      }
    }   
    word=strtok(NULL,space);
  }
  if(wrgandor){
    printf("And/or can not be at the end\n");
    return NULL;
  }
  if(numwrd>maxwrd-1){
    printf("Six Word Maximun\n");
    return NULL;
  }
  return format;
}

//makes lowercase
static void mklower(char *line){
  while(*line!='\0'){
    *line=tolower(*line);
    line++;
  }
}
//checks string to see if its only whitespace
static bool checkemp(char *line){
  while(*line==' '){
    line++;
  }
  if(*line=='\0'){
    return true;
  }
  return false;
}
static void addor(char *line,hashtable_t *index,char *dir){
  int list=0;
  bool newitem=true;
  char *word;
  orderlist_t **score=malloc(6*sizeof(orderlist_t));
  for (int i=0;i<=maxwrd;i++){
    score[i]=NULL;
  }
  word=strtok(line," ");
  while(word!=NULL){
    if (newitem){
      score[list]=orderlist_new(delete,index,word);
      //counters_iterate(hashtable_find(index,word),lsprint,NULL);
      //orderlist_iterate(score[list],lsprint,NULL);
      newitem=false;
    }
    else if (strcmp(word,or)==0){
      word=strtok(NULL," ");
      list++;
      score[list]=orderlist_new(delete,index,word);
      //orderlist_iterate(score[list],lsprint,NULL);
    }
    else{
      score[list]=orderlist_and(score[list],index,word);
      //orderlist_iterate(score[list],lsprint,NULL);
    }
    word=strtok(NULL," ");
  }
  int j=0;
  while(j<maxwrd&&score[j]==NULL){
    j++;
  }
  for (int i=j+1;i<maxwrd;i++){
    if (score[j]!=NULL&&score[i]!=NULL){
      orderlist_or(score[j],score[i]);
    }
  }
  printf("Value:%d\n",j);
  if (score[j]!=NULL)
  orderlist_iterate(score[j],lsprint,dir);
    orderlist_delete(score[j]);
  free(score);
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
static void getWords(hashtable_t* ht, FILE* file){

  char* word;//string extracted from file to be precessed
  char* wordT;//word to insert into table
  int idNum;
  int numOccur;

  //if the word is null then the file is ended
  while((word = readword(file)) != NULL){
    if(strcmp(word,"")==0){
      	free(word);
	continue;
    }
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
//delete a counter
static void delete(void *data){
  counters_t *ctrs=data;
  counters_delete(ctrs);
}
static void lsprint(void *arg, int idnum, int score){
  char *dir=arg;
  char *url=geturl(idnum,dir);
  printf("idnum:%d, score:%d, url:%s\n",idnum,score,url);
  free(url);
}


//gets url
static char *geturl(int idnum, char* dir){
  int length = snprintf(NULL,0,"%s/%d",dir,idnum);
  char* fName;//make name of file
  if((fName = malloc(length+1)) == NULL)
    return NULL;
  if(snprintf(fName,length+1,"%s/%d",dir,idnum)<0)
    return NULL;
  //open file and read line
  FILE *fp=fopen(fName,"r");
  free(fName);
  char *line=readline(fp);
  fclose(fp);
  return line;
}
