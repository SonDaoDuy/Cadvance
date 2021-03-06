#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#define CSV "data.csv"

typedef struct{
  char* name;
  char* tel;
}person;


person* get_data_from_file(FILE *fp,int size);

int count_line(FILE* fp);

void add_to_tree(JRB* t,person* arr,int size);

int main(){
  FILE* fin = fopen(CSV, "r");
  if(fin == NULL){
    fprintf(stderr,"Can't open file %s\n",CSV);
    exit(1);
  }

  int size = count_line(fin);

  JRB t,tmp;

  t = make_jrb();

  person *arr = get_data_from_file(fin,size);

  add_to_tree(&t,arr,size);

  free(arr);

  jrb_traverse(tmp, t){
          char *name = tmp->key.s;
          char *tel = (char *)tmp->val.v;
          printf("%-s %-s\n", name, tel);
     }

  char name[40];
  printf("Enter name to find: ");
  scanf("%[^\n]",name);

  JRB find = jrb_find_str(t,name);
  if(find == NULL){
    printf("NOT FOUND!!!\n");
  }
  else{
    printf("%-s   %-s\n",find->key.s,find->val.s);
  }

  jrb_traverse(tmp,t){
    free(tmp->key.s);
    free(tmp->val.v);
  }

  jrb_free_tree(t);
  fclose(fin);
  return 0;
}

void add_to_tree(JRB* t,person* arr,int size){
  if(t==NULL){
    fprintf(stderr,"NULL value error in %s:%d!!\n",__FILE__,__LINE__);
    exit(1);
  }
  int i;
  for(i = 0;i < size; i++){
    jrb_insert_str(*t,arr[i].name,new_jval_v((void*)arr[i].tel));
  }
}

int count_line(FILE* fp){
  char s[1000];
  int count = 0;
  while(fgets(s,1000,fp) != NULL)
    count++;
  rewind(fp);
  return count;
}

person* get_data_from_file(FILE* fp,int size){
  person * ret = (person*) malloc(sizeof(person)*size);
  if(ret==NULL){
    fprintf(stderr,"Malloc failed %s:%d!!!\n",__FILE__,__LINE__);
    exit(1);
  }

  int i;
  for(i = 0;i < size; i++){
    char name[40],tel[40];
    fscanf(fp,"%[^|]|%[^|]|%*[^|]|%*[^\n]\n",name,tel);

    ret[i].name = (char*)malloc(strlen(name)+1);
    ret[i].tel = (char*)malloc(strlen(tel)+1);

    if(ret[i].name == NULL || ret[i].tel == NULL){
      fprintf(stderr,"Read value failed %s:%d!!!\n",__FILE__,__LINE__);
      exit(1);
    }
    strcpy(ret[i].name,name);
    strcpy(ret[i].tel,tel);
  }
  return ret;
}

