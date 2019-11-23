#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 50

#define arraySearch(x, y, z) multiSearch(x, y, z)

int answer;

typedef struct threadSearch_args {
    int** _array;
    int thread_num;
    int numToFind;
    int arrayLength;
}argt;