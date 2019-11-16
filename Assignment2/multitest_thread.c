#include "multitest.h"

void* threadedSearch(void*);

int multiSearch(int** _array, int numToFind) {
    pthread_t* threads = (pthread_t*) malloc(NUM_THREADS * sizeof(pthread_t));
  
    argt threadArgs;
    threadArgs.array = *_array;
    threadArgs.numToFind = numToFind;

    int i; int j;
    for (i = 0; i < NUM_THREADS; i++) {
        threadArgs.thread_num = i;

        pthread_create(&threads[i], NULL, multiSearch, (void*) &threadArgs);
    }

    int* _foundIndex = (int*) malloc(sizeof(int));
    for (j = 0; j < NUM_THREADS; j++) {
        pthread_join(threads[j], &_foundIndex);
        if (*_foundIndex >= 0) {
            free(threads);
            return *_foundIndex;
        }
    }

    free(threads);
    return -1;
}

void* threadedSearch(void* args) {
    int* array = ((argt*) args)->array;
    int threadNum = ((argt*) args)->thread_num;
    int numToFind = ((argt*) args)->numToFind;
    int arrayLength = sizeof(array)/sizeof(int);

    int chunkSize = arrayLength/NUM_THREADS;
    int startIndex = chunkSize*threadNum;
    int endIndex = chunkSize*(threadNum + 1);

    if (threadNum == NUM_THREADS - 1)
        endIndex = arrayLength;

    int i;
    for (i = startIndex; i < endIndex; i++) {
        if (array[i] == numToFind) {
            pthread_exit(&i);
        }
    }
}