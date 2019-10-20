#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

char myblock[4096];

typedef struct Metadata {
    int is_in_use;
    int pointer_size;
} Metadata;

void* mymalloc(size_t size, char* file, int line);
Metadata getMetadata(int index);
void myfree(void* ptr, char* file, int line);