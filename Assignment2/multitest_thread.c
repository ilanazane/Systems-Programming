#include "multitest.h"

int multiSearch(int**, int, int);
void* threadedSearch(void*);

int multiSearch(int** _array, int arrayLength, int numToFind) {
    pthread_t* threads = (pthread_t*) malloc((numThreads) * sizeof(pthread_t));

    argt** arglist = (argt**) malloc(numThreads*sizeof(argt*));

    int i; int j;
    for (i = 0; i < numThreads; i++) {
        argt* threadArgs = malloc(sizeof(argt));
        threadArgs->_array = _array;
        threadArgs->numToFind = numToFind;
        threadArgs->arrayLength = arrayLength;
        threadArgs->thread_num = i;
        arglist[i] = threadArgs;
        pthread_create(&threads[i], NULL, &threadedSearch, (void*) arglist[i]);
    }
    int ret;
    void* foundIndex = -1;
    for (j = 0; j < numThreads; j++) {
        ret = -1;
        pthread_join(threads[j], &foundIndex);
        if ((int)foundIndex >= 0) {
            ret = (int) foundIndex;
            printf("final num: %d\n", (int) foundIndex);
            break;
        }
        
        
    }
    // printf("final num: %d\n", (int) foundIndex);

    free(threads);
    return ret;
}

void* threadedSearch(void* args) {
    int* array = (*((argt*) args)->_array);
    int threadNum = ((argt*) args)->thread_num;
    int numToFind = ((argt*) args)->numToFind;
    int arrayLength = ((argt*) args)->arrayLength;

    int chunkSize = arrayLength/numThreads;
    int startIndex = chunkSize*threadNum;
    int endIndex = chunkSize*(threadNum + 1);

    if (threadNum == numThreads - 1) {
        endIndex = arrayLength;
    } 
    // else if (threadNum < 0) {
    //     pthread_exit((void*)-1);
    // }
    
    // printf("thread %d startI = %d\n", threadNum, startIndex);
    // printf("thread %d endI = %d", threadNum, endIndex);

    int i;
    for (i = startIndex; i < endIndex; i++) {
        if (array[i] == numToFind) {
            // printf("i = %d\n", i);
            pthread_exit((void*)i);
        }
    }
    pthread_exit((void*)-1);
}