#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN 20
#define MAX 10000000

int* generate(int size){
  int i;
  int* a;
  a = (int*) malloc(sizeof(int)*size);
  srand(time(NULL));
  for(i = 0; i < size; i++){
    a[i] = 1 + rand()%10;
  }
  return a;
}
void exchange(int a[],int l,int r){
  int hold;
  hold = a[l];
  a[l] = a[r];
  a[r] = hold;
}

void quicksort2w(int *a,int l,int r){
  if(r<=l) return;
  int i = l-1, j =r;
  int p = l-1, q =r;
  while(1){
    while(a[++i] < a[r]);
    while(a[r] < a[--j]) if(j==l) break;
    if(i>=j) break;
    exchange(a,i,j);
  }
  exchange(a,i,r);
  j = i-1;
  i = i+1;
  quicksort2w(a,l,j);
  quicksort2w(a,i,r);
}

void quicksort3w(int *a,int l,int r){
  if(r<=l) return;
  int i = l-1, j =r;
  int p = l-1, q =r;
  while(1){
    while(a[++i] < a[r]);
    while(a[r] < a[--j]) if(j==l) break;
    if(i>=j) break;
    exchange(a,i,j);
    if(a[i] == a[r]) exchange(a,++p,i);
    if(a[j] == a[r]) exchange(a,--q,j);                    
                       
  }
  exchange(a,i,r);
  j = i-1;
  i = i+1;
  int k;
  for(k = l; k <= p;k++) exchange(a,k,j--);
  for(k = r-1; k >= q; k--) exchange(a,k,i++);
  quicksort3w(a,l,j);
  quicksort3w(a,i,r);
}

void printsort(int a[],int size){
  int i;
  for(i = 0;i < size;i++){
    printf("%d ",a[i]);
  }
  printf("\n");
}
int main(){
  int *a;
  int* b;
  a = generate(MAX);
  b = generate(MAX);
  

  clock_t start,end;
  double cpu_time;
  start =clock();
  quicksort2w(a,0,MAX-1);
  end = clock();
  cpu_time = ((double) (end - start))/CLOCKS_PER_SEC;
  printf("2w Run in %f seconds.\n",cpu_time);
  
  free(a);
 
  start =clock();
  quicksort3w(b,0,MAX-1);
  end = clock();
  cpu_time = ((double) (end - start))/CLOCKS_PER_SEC;
  printf("3w Run in %f seconds.\n",cpu_time);
  
  free(b);
}
