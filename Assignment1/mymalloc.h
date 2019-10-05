#include <stdlib.h>
#include <stdio.h>

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

static char myblock[4096];

typedef struct Metadata {
    int is_in_use;
    int pointer_size;
} Metadata;

void* mymalloc(size_t size);
Metadata getMetadata(int index);
int checkIfMetadata();
void myfree(void* ptr);