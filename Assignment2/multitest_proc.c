#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <math.h> 
#include <sys/wait.h> 
#include "multitest.h"

int multiSearch(int**, int);
int pSearch(int*, int, int, int, int, int)

int multiSearch(int** array, int numToFind){


	//pid_t pid=fork(); 
	int size=sizeof(array)/sizeof(array[0]); 
	double groups =size/250; 
	//printf("groups: %lf",groups);
	double loggroups= log(80.0)/log(2); 
	double numOfForks=  ceil(loggroups); 
	//printf("loggroups: %lf",numOfForks); 


	//pSearch(arr,0,20000,0,250,key); 
	
	printf("%d\n",pSearch(array,0,20000,0,250,numToFind));  
	

  //return 0;
}

int pSearch(int* array,int startIndex, int endIndex, int currentLevel, int maxSize,int numToFind) { 
	int status; 
	if (endIndex - startIndex > maxSize) { 

		pid_t pid = fork();
 
		int newChunkSize = (endIndex - startIndex) / 2;

		if (pid ==0){
 			pid= wait(&status);
			int newEndIndex = endIndex - newChunkSize;  
			pSearch(array, startIndex, newEndIndex, ++currentLevel, maxSize,numToFind);
			wait(NULL);  

		} else {
			int newStartIndex = startIndex + newChunkSize;

			pSearch(array, newStartIndex, endIndex, ++currentLevel, maxSize,numToFind);
			wait(NULL); 
		}
	}
	int i=0;
	for(i=startIndex;i<endIndex;i++){
		if(array[i]==numToFind){
			//printf("%d\t",i);   
			return i; 
			 //wait(NULL); 
		}
	}
}
