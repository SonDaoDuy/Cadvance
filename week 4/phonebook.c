#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#define CSV "data.csv"
#define fid "b_tree_file.txt"



typedef struct{
  char* name;
  int tel;
}person;

int count_line(FILE *fp);

person* get_data_from_file(FILE *fin,int size);

void add_data_to_tree(BTA *t,person* arr,int size);

int main(){
  btinit();
  BTA *t;
  FILE *fin = fopen(CSV,"r");
  if(fin==NULL){
    fprintf(stderr,"Cannot open file input %s:%d!!!\n",__FILE__,__LINE__);
    exit(1);
  }
  int size = count_line(fin);
  btcrt(fid,size,0);
  t = btopn(fid,0,0);
  
  //insert data to tree
  
  
  person *new_info = get_data_from_file(fin,size);
  
  add_data_to_tree(t,new_info,size);
  free(new_info);
  
  btcls(t);
}


int count_line(FILE* fp){
  char s[1000];
  int count = 0;
  while(fgets(s,1000,fp) != NULL)
    count++;
  rewind(fp);
  return count;
}

person* get_data_from_file(FILE *fin,int size){
  person* ret =(person*) malloc(sizeof(person)*size);
  if(ret == NULL){
    fprintf(stderr,"Malloc failed %s:%d!!!\n",__FILE__,__LINE__);
    exit(1);
  }
  int i;
  for(i = 0;i < size; i++){
    char name[40];
    int tel;
    fscanf(fin,"%[^|]|%d|%*[^|]|%*[^\n]\n",name,&tel);
    ret[i].name = (char*)malloc(strlen(name)+1);
    if(ret[i].name == NULL){
      fprintf(stderr,"Read value failed %s:%d!!!\n",__FILE__,__LINE__);
      exit(1);
    }
    strcpy(ret[i].name,name);
    ret[i].tel = tel;
  }
  return ret;
}

void add_data_to_tree(BTA *t,person* arr,int size){
  if(t == NULL){
    fprintf(stderr,"NULL value error %s:%d!!1\n",__FILE__,__LINE__);
    exit(1);
  }
  
  int i;
  for(i = 0;i < size; i++){
    binsky(t,arr[i].name,arr[i].tel);
  }
}
