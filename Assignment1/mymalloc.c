#include "mymalloc.h"

void* mymalloc(size_t size, char* file, int line) {

    int block_size = 4096;
    int metadata_size = 2;
    int new_ptr_size = (int) size;

    if (new_ptr_size > block_size - metadata_size || new_ptr_size == 0) {
        printf("Malloc() Error: Saturation of dynamic memory on line %d of file \"%s\"\n", line, file);
        return NULL;
    }
    int i = 2; 
    char byte1; char byte2;

    while (i < block_size) {
        Metadata metadata = getMetadata(i);
        // static arrays are always zero-initialized, allowing predictable behavior
        if (!metadata.is_in_use) {
            // Set Metadata
            byte1 = ((char)(new_ptr_size / 100)) | -128;
            byte2 = (char)(new_ptr_size % 100);

            int return_index = i; int j; int is_too_small = 0;

            for (j = i; j < (new_ptr_size + return_index); j++) {
                // myblock[j] == 0 if location j is unallocated
                if (myblock[j] < 0) {
                    i = j;
                    is_too_small = 1;
                }
            }

            if (!is_too_small) {
                myblock[return_index - 2] = byte1;
                myblock[return_index - 1] = byte2;
                return (void*) &myblock[return_index];
            }
            
        } else {
            i += metadata.pointer_size + metadata_size;
        }
    }
    // End of array reached
    printf("Malloc() Error: Saturation of dynamic memory on line %d of file \"%s\"\n", line, file);
    return NULL;
}

Metadata getMetadata(int ptrIndex) {
    int metadata_size = 2;
    int index = ptrIndex - metadata_size;
    Metadata metadata;

    char byte1 = myblock[index];
    char byte2 = myblock[index + 1];

    int byte1_limit = (4094 - index) / 100;
    int byte2_limit = 99;

    metadata.is_in_use = (byte1 >> 7) & 1;
    metadata.pointer_size = (byte1 & 127) * 100 + byte2;

    if (metadata.pointer_size > 4094 || (byte1 & 127) > byte1_limit || byte2 > byte2_limit || byte2 < 0) {

        metadata.is_in_use = 0;
        metadata.pointer_size = 0;

    }

    return metadata;
}

void myfree(void* ptr, char* file, int line) {

    int index = ((char*) ptr - myblock) / sizeof(char);
    int block_size = 4096;

    if (index >= block_size || index < 2 || ((uintptr_t) ptr < block_size && ptr > 0)) {
        printf("Free() Error: Address out of bounds on line %d of file \"%s\"\n", line, file);
        ptr = NULL;
        return;
    }

    Metadata metadata = getMetadata(index);

    if (!metadata.is_in_use) {
        printf("Free() Error: Freeing unallocated pointer on line %d of file \"%s\"\n", line, file);
        ptr = NULL;
        return;
    }
    // Clearing metadata
    myblock[index - 2] = 0;
    myblock[index - 1] = 0;

    int i;
    for (i = index; i < metadata.pointer_size + index; i++) {
        // Clearing data
        myblock[i] = 0;
    }
    ptr = NULL;
}