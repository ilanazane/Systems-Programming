#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <math.h> 
#include <sys/wait.h> 
#include "multitest.h"

int multiSearch(int**,int,int); 

int pSearch(int*, int, int , int , int , int,int );  

int  multiSearch(int** array,int arrayLength, int numToFind){  
	

	int final=pSearch(*array,arrayLength,0,arrayLength-1,0,250,numToFind);  
	// exit(0);
	printf("final: %d",final);
	

  	return 0;
}

int pSearch(int* array,int arrayLength,int startIndex, int endIndex, int currentLevel, int maxSize,int numToFind) { 
	int status; 
	
	if (arrayLength - 1 - startIndex > maxSize) { 

		pid_t pid = fork();
 
		int newChunkSize = (endIndex - startIndex) / 2;

		if (pid ==0){
 			
			int newEndIndex = endIndex - newChunkSize;  
			return pSearch(array, arrayLength, startIndex, newEndIndex, ++currentLevel, maxSize, numToFind);
			  

		} else {
			int newStartIndex = startIndex + newChunkSize;
			// int newEndIndex = newStartIndex + newChunkSize;
			return pSearch(array, arrayLength, newStartIndex, endIndex, ++currentLevel, maxSize, numToFind);
			
		}
	}
	int i=0;
	for(i=startIndex;i<endIndex;i++){
		if(array[i]==numToFind){
			//exit(0); 
			printf("here: %d\t",i);
			break;
			//return i; 
			  
		}   
		

	}

	return i; 
}
