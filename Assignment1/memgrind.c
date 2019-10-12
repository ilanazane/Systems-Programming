#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> 
#include "mymalloc.h"



int main(){

int caseA; 
int caseB; 
int caseC; 
int caseD; 

int x; 
int y; 

int* array[50];

struct timeval start; 
struct timeval finish; 
	//CASE A: malloc 1 byte and immediately free it- do this 150 times 
	for(y=0;y<150;y++){
	gettimeofday(&start,0); 
		for(x=0;x<50;x++){
			array[x]=(int*)malloc(1); 
			myfree(array[x]); 
			array[x]=NULL;
		}
	gettimeofday(&finish,0); 
	caseA+=(finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec); 
	
	}
	//printf("A %d", caseA/100); 


//CASE B: malloc 1 byte and store in array- do this 150 times 
//once you've malloced 50 bytes, free each one, one by one 

	for(y=0;y<150;y++){
		gettimeofday(&start,0); 
			for(x=0;x<50;x++){
				array[x]=(int*)malloc(1); 
			}
				for(x=0;x<50;x++){
					myfree(array[x]); 
					array[x]=NULL; 
				}	
	gettimeofday(&finish,0);
	caseB+=(finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec);
	}


//CASE C: randomly malloc or free 
int numAllocs=0;
int numMallocs=0; 
int numFrees=0; 
int mallORfree= 0+rand()%2;  


	for(y=0;y<100;y++){
		gettimeofday(&start,0); 
		srand(time(NULL)); 
		while(numAllocs<50){
			if(mallORfree==1){
				array[numMallocs]=(int*)malloc(1); 
			}if(!array[numMallocs]==NULL){
				numMallocs++; 
				numAllocs++; 
			}else{
				myfree(array[numFrees]);
				array[numFrees]=NULL; 
				numFrees++; 
			}		
		}//end of while loop 
		if(mallORfree==0){
				myfree(array[numFrees]); 
				array[numFrees]=NULL; 
				numFrees++; 
			}
		mallORfree=0+rand()%2; 
		
	gettimeofday(&finish,0); 
	caseC+=(finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec);
	}//end of for loop 


//CASE D: randomly choose between 1-64 byte malloc or free 

//int numAllocs=0; 
//int numMallocs=0; 
//int numFrees=0; 

//int mallORfree=0+rand()%2; 
int randomBytes= 1+rand()%65;	
	
	for(y=0;y<100;y++){
		gettimeofday(&start,0); 
		srand(time(NULL));

		while(numAllocs<50){
			if(mallORfree==1){
				array[numMallocs]=(int*)malloc(1); 
			}if(!array[numMallocs]==NULL){
				numMallocs++; 
				numAllocs++; 
			}else{
				myfree(array[numFrees]);
				array[numFrees]=NULL; 
				numFrees++; 
			}		
		}//end of while loop 
		if(mallORfree==0){
			myfree(array[numFrees]); 
			array[numFrees]=NULL; 
			numFrees++; 
			
		}
		for(x=numFrees;x<50;x++){
			myfree(array[x]);
			array[x]=NULL;
		}
		
		
	gettimeofday(&finish,0); 
	caseD+=(finish.tv_sec-start.tv_sec) + (finish.tv_usec-start.tv_usec);
	}


	printf("A %d\n",caseA/100); 
	printf("B %d\n",caseB/100); 
	printf("C %d\n",caseC/100); 
	printf("D %u\n",caseD/100); 





return 0; 
}
