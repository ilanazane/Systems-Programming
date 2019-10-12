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

int i; 
int j; 

int* array[50];

struct timeval start; 
struct timeval finish; 
	//CASE A: malloc 1 byte and immediately free it- do this 150 times 
	for(j=0;j<150;j++){
	gettimeofday(&start,0); 
		for(i=0;i<50;i++){
			array[i]=(int*)malloc(1); 
			myfree(array[i]); 
			array[i]=NULL;
		}
	gettimeofday(&finish,0); 
	caseA=caseA+((finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec)); 
	
	}
	//printf("A %d", caseA/100); 


//CASE B: malloc 1 byte and store in array- do this 150 times 
//once you've malloced 50 bytes, free each one, one by one 

	for(j=0;j<150;j++){
		gettimeofday(&start,0); 
			for(i=0;i<50;i++){
				array[i]=(int*)malloc(1); 
			}
				for(i=0;i<50;i++){
					myfree(array[i]); 
					array[i]=NULL; 
				}	
	gettimeofday(&finish,0);
	caseB=caseB+((finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec));
	}


//CASE C: randomly malloc or free 
int numAllocs=0;
int numMallocs=0; 
int numFrees=0; 
int mallORfree= 0+rand()%2;  

	for(j=0;j<100;j++){
		gettimeofday(&start,0); 
		srand(time(NULL)); 
		while(numAllocs<50){
			if(mallORfree==1){
				array[numMallocs]=(int*)malloc(1); 
			}if(!array[numMallocs]==NULL){
				numMallocs++; 
				numAllocs++; 
			}else{
				myfree(array[numMallocs]);
				array[numMallocs]=NULL; 
				numFrees++; 
			}		
		}//end of while loop 
	}//end of for loop 


	printf("A %d\n",caseA/100); 
	printf("B %d\n",caseB/100); 
