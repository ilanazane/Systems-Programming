#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> 
#include "mymalloc.h"



int main(){

	int caseA = 0; 
	int caseB = 0; 
	int caseC = 0; 
	int caseD = 0; 
	int caseE = 0;
	int caseF = 0;

	int x; 
	int y; 

	int* ptrArray[150];
	char* strArray[60];

	struct timeval start;
	struct timeval finish;


	//CASE A: malloc 1 byte and immediately free it- do this 150 times

	gettimeofday(&start,0);

	for (y = 0; y < 100; y++) {
		 
		for(x = 0; x < 150; x++){
			ptrArray[x]= (int*) malloc(1); 
			free(ptrArray[x]);
		}
	}

	gettimeofday(&finish,0); 
	caseA += (finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec); 
	

	//CASE B: malloc 1 byte and store in ptrArray- do this 150 times 
	//once you've malloced 50 bytes, free each one, one by one 

	int z;
	gettimeofday(&start,0);

	for (y = 0; y < 100; y++) {
		
		for(z = 0; z < 3; z++){
			 
			for(x = 0; x < 50; x++){
				ptrArray[x]=(int*)malloc(1); 
			}
			for(x = 0; x < 50; x++){
				free(ptrArray[x]);
			}
		}
	}

	gettimeofday(&finish,0);
	caseB += (finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec);


	//CASE C: Randomly malloc or free until 50 malloc calls.
	int numMallocCalls = 0;
	int numPtrs = 0;
	srand(time(NULL));
	int doMalloc = rand() & 1;

	gettimeofday(&start,0); 

	for (y = 0; y < 100; y++) {
		while (numMallocCalls < 50){
			if (doMalloc){
				ptrArray[numPtrs] = (int*) malloc(1);
				numPtrs++;
				numMallocCalls++;
			} else if (numPtrs > 0){
				free(ptrArray[--numPtrs]);
			}
			doMalloc = rand() & 1;
		}
		while (numPtrs > 0)	{
			free(ptrArray[--numPtrs]);
		}
	}

	gettimeofday(&finish,0); 
	caseC += (finish.tv_sec - start.tv_sec)*1000000 + (finish.tv_usec - start.tv_usec);


	//CASE D: randomly choose between 1-64 byte malloc or free 

	numMallocCalls = 0;
	numPtrs = 0;
	srand(time(NULL));
	doMalloc = rand() & 1;
	int ptrSize = rand() % 65;
	
	gettimeofday(&start,0);

	for (y = 0; y < 100; y++) {
		
		while (numMallocCalls < 50){
			if (doMalloc){
				ptrArray[numPtrs] = (int*) malloc(ptrSize);
				numPtrs++;
				numMallocCalls++;
			} else if (numPtrs > 0){
				free(ptrArray[--numPtrs]);
			}
			doMalloc = rand() & 1;
		}
		while (numPtrs > 0)	{
			free(ptrArray[--numPtrs]);
		} 
	}

	gettimeofday(&finish,0); 
	caseD += (finish.tv_sec - start.tv_sec)*1000000 + (finish.tv_usec - start.tv_usec);


	// CASE E: Storing strings in the malloc'd pointers and immediately freeing those pointers.
	
	int i; int j;
	char* inputStr = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";

	gettimeofday(&start, 0);

	for (y = 0; y < 100; y++) {
		for (i = 0; i < 50; i++) {
			char* ptrE = (char*) malloc(60);
			j = 0;
			do {
				ptrE[j] = inputStr[j];
				j++;
			} while (inputStr[j - 1] != '\0');
		
			free(ptrE); 
		}
	}

	gettimeofday(&finish,0); 
	caseE += (finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec);	




	// CASE F: Storing strings in the malloc'd pointers and freeing all those pointers at once at the end.



	int k;
	char* tempAddress;
	
	gettimeofday(&start, 0);

	for (y = 0; y < 100; y++) {
		for (i = 0; i < 50; i++) {
			strArray[i] = (char*) malloc(60);
			j = 0;
			do {
				tempAddress = (char *) (strArray[i]) + j;
				*tempAddress = inputStr[j];
				j++;
			} while (inputStr[j - 1] != '\0');
		}
		for (k = 0; k < 50; k++) {
			free(strArray[k]);
		}
	}

	gettimeofday(&finish,0); 
	caseF += (finish.tv_sec - start.tv_sec)*1000000 + (finish.tv_usec - start.tv_usec); 


	printf("A %.2f microseconds\n", caseA/100.0);
	printf("B %.2f microseconds\n", caseB/100.0);
	printf("C %.2f microseconds\n", caseC/100.0);
	printf("D %.2f microseconds\n", caseD/100.0);
	printf("E %.2f microseconds\n", caseE/100.0);
	printf("F %.2f microseconds\n", caseF/100.0);

	return 0; 
}
