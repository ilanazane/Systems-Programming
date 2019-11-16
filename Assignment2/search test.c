#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b){
  int temp=*a;
  *a=*b;
  *b=temp;
}

void printArray(int arr[], int n){
  int i=0;
  for(i=0;i<n;i++){
    printf("%d",arr[i]);
  }
}

void randomize(int arr[],int n){
  //use a different seed value so that we dont get
  //same result each time we run
  srand(time(NULL));
  int i=0;
  for(i=n-1;i>0;i--){
    int j=rand()%(i+1);
    swap(&arr[i],&arr[j]);
  }
}

int main(){
  int arr[20001];
  int i=0;
  for(i=0;i<=20000;i++){
    arr[i]=i;
  }
  int n=sizeof(arr)/sizeof(arr[0]);
  randomize(arr,n);
  printArray(arr,n);

  return 0;
}
