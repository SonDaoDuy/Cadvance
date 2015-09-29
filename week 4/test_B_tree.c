#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#define file_name "test_B-tree.txt"
#define MAX 3

void clear_buffer(){
  while(getchar()!='\n');
}
int main(){
  btinit();
  BTA *t,*t1;
  BTint value = 1;
  char name[30];
  int i;
  t = btcrt(file_name,MAX,0);
  
   printf("NHap ten thu : ");
    scanf("%[^\n]",name);
    clear_buffer();
    printf("%d \n",binsky(t,name,value));
  for(i = 0; i < MAX; i++ ){
    printf("NHap ten thu %d: ",i);
    scanf("%[^\n]",name);
    clear_buffer();
    printf("%d \n",binsky(t,name,i));
  }
  
  btcls(t);
}
