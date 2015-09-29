#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN 10
#define MAX 100

int int_compare(void* x,void* y){
  int m,n;
  m = *((int*)x);
  n = *((int*)y);
  if(m==n) return 0;
  return m>n?1:-1;
}

void exch(void* buf,int size,int i,int j){
  int hold;
  hold = *((int*)((char*)buf+i*size));
  *((int*)((char*)buf+i*size)) = *((int*)((char*)buf+j*size));
  *((int*)((char*)buf+j*size)) = hold;
}

int search(void* buf,int size,int l,int r, void* item,int (*compare)(void*,void*)){
  if(r<l) return -1;
  i = (l+r)/2;
  res = compare(item,(char*)buf+i*size);
  if(res==0)
    return i;
  else
    if(res < 0)
      return search(buf,size,l,i-1,item,compare);
    else
      return search(buf,size,i+1,r,item,compare);
}

void sort(void* a,int size,int l,int r,int (*compare)(void*,void*)){
  if(r<=l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1){
    while(compare((char*)a+(++i)*size, (char*)a+r*size)<0);
    while(compare((char*)a+r*size,(char*)a+(--j)*size)<0)
      if(j==l) break;
    if(i >= j) break;
    exch(a,size,i,j);
    if(compare((char*)a+i*size,(char*)a+r*size)==0)
      exch(a,size,++p,i);
    if(compare((char*)a+j*size,(char*)a+r*size)==0)
      exch(a,size,--q,j);
  }
  exch(a,size,i,r);
  j = i-1;
  i = i+1;
  int k;
  for(k = l; k <= p;k++) exch(a,size,k,j--);
  for(k = r-1;k>=q; k--) exch(a,size,k,i++);
  sort(a,size,l,j,compare);
  sort(a,size,i,r,compare);
}

int main(){
  int a[MIN];
  int n=MIN,item=5;
  int i;
  srand(time(NULL));
  for(i=0;i<n;i++)
    a[i] = 1+rand()%10;
  sort(a,sizeof(int),0,n-1,int_compare);
  for(i=0;i<n;i++)
    printf("%d ",a[i]);
  printf("\n");
}
