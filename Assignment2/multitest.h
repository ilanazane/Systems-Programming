#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

#define arraySearch(x, y) multiSearch(x, y)

typedef struct threadSearch_args {
    int* array;
    int thread_num;
    int numToFind;
}argt;

int multiSearch(int**, int);