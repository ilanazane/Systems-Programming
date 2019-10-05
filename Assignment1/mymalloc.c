#include "mymalloc.h"

void* mymalloc(size_t size) {
    int block_size = 4096;
    int metadata_size = 2;
    int new_ptr_size = (int) size;

    if (new_ptr_size > block_size - metadata_size || new_ptr_size == 0) {
        printf("Malloc Error A: Saturation of dynamic memory on line %d of file \"/s\"\n", __LINE__, __FILE__);
        return NULL;
    }
    int i = 0; char data; char byte1; char byte2;

    for (i = 1; i < block_size - metadata_size; i++) {
        data = myblock[i];
        // static arrays are zero-initialized in C
        if (data == 0) {
            // Set Metadata
            byte1 = ((char)(new_ptr_size / 100)) & -127;
            byte2 = (char)(new_ptr_size % 100);

            i += 2;
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
            
        } else if (data < 0) {
            Metadata metadata = getMetadata(i);
            if (metadata.pointer_size == 0) {
                // Do nothing, go to next iteration
            } else {
                i += metadata.pointer_size + metadata_size;
            }

        } else {
            // Do nothing, go to next iteration
        }
    }
    // End of array reached
    printf("Malloc Error A: Saturation of dynamic memory on line %d of file \"/s\"\n", __LINE__, __FILE__);
    return NULL;
}

Metadata getMetadata(int index) {
    Metadata metadata;

    char byte1 = myblock[index];
    char byte2 = myblock[index + 1];

    int byte1_limit = (4094 - index) % 100;
    int byte2_limit = 99;

    metadata.is_in_use = (byte1 >> 7) & 1;
    metadata.pointer_size = (byte1 & 127) * 100 + byte2;

    if (metadata.pointer_size > 4094 || (byte1 & 127) > byte1_limit || byte2 > byte2_limit) {
        metadata.pointer_size = 0;
        metadata.is_in_use = 0;
    }
    return metadata;
}