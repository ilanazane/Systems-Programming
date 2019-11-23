#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "multitest.h"

void swap(int*, int*);
void printArray(int*, int);
void randomize(int*, int);
// int arraySearch(int**, int);

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

int main(int argc, char** argv){
  int arrayLength = 2001;
  int numToFind = 50;

  printf("Multi-mode = %s\n", (argv[0]) + 2);

  int* array = (int*) malloc(arrayLength * sizeof(int));
  
  int i = 0;
  for(i = 0; i < arrayLength; i++){
    array[i] = i;
  }

  randomize(array, arrayLength);

  // find index for answer verification
  int a;
  for (a = 0; a < arrayLength; a++) {
    if (array[a] == numToFind) {
      printf("answer = %d\n", a);
      answer = a;
    }
      
  }

  int foundIndex = arraySearch(&array, arrayLength, numToFind);
  // printf("findex = %d\n", foundIndex);
  free(array);
  return 0;
}

// int arraySearch(int ** array, int numToFind) {
//   // Do nothing
//   return 0;
// }
