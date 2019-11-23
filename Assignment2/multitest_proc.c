#include <unistd.h> 
#include <math.h> 
#include <sys/wait.h> 
#include "multitest.h"

int multiSearch(int**,int,int); 

// int pSearch(int*, int, int , int , int , int,int ); 

int multiSearch(int** _array,int arrayLength, int numToFind){  
	int i = 0; int j; int k;
    int numProcesses = ceil(((double)arrayLength)/((double)maxSize));
    int chunkSize = ceil(((double)arrayLength)/((double)numProcesses));
    int multiplier = 0;
    int startIndex = 0;
    int endIndex = chunkSize;
    int* array = *_array;
    int status;
    // int first = fork();
    int children[numProcesses];

    for (i = 0; i < numProcesses; i++) {
        children[i] = fork();
        if (children[i] == 0) {
            multiplier = i;
            startIndex += (chunkSize*multiplier);
            endIndex += (chunkSize*multiplier);

            for (j = startIndex; j < endIndex; j++) {
                if (array[j] == numToFind) {
                    printf("FOUND AT: %d\n", j);
                    return j;
                    // exit(j - startIndex);
                }
            }
            exit(251);
        } else {
            waitpid(children[i], &status, 0);
            return -1;
            // int returned = 251;
            // if (WIFEXITED(status))
            //     returned = WEXITSTATUS(&status);
            // if (returned < 251) {
            //     printf("return: %d\n", (returned + (i*chunkSize)));
            //     return (returned + (i*chunkSize));
            // }
        }

    }
       
}