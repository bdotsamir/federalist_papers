// REFERENCES:
// [1]: https://clang.llvm.org/extra/clang-tidy/checks/bugprone/suspicious-realloc-usage.html

#include <stdlib.h>
#include <stdio.h>
#include "array.h"

void initArray(Array *a, const size_t initialSize) {
    if(initialSize == 0) {
        fprintf(stderr, "Cannot initialize array with size 0\n");
        exit(EXIT_FAILURE);
    }

    a->array = calloc(initialSize, sizeof(int));
    if(!a->array) {
        fprintf(stderr, "Failed to allocate memory of size %lu\n", initialSize);
        exit(EXIT_FAILURE);
    }

    a->used = 0;
    a->size = initialSize;
}

void push(Array *a, int data) {
    // If the array has already reached its maximum size,
    if(a->size == a->used) {
        // Set the new size to itself times 2.
        // This could be optimized, but we have virtually unlimited memory, so it isn't too bad.
        // It's not like we're embedded programmers lul
        // See other: https://stackoverflow.com/a/1100426/8916706

        // Actually reallocate that block of memory to the new size
        int *p = reallocarray(a->array, a->size *= 2, sizeof(int));
        // If the reallocation fails, exit.
        if(!p) {
            fprintf(stderr, "Failed to reallocate array of new size %lu\n", a->size);
            exit(EXIT_FAILURE);
        }
        a->array = p; // REF: [1]
//        fprintf(stderr, "[DEBUG] Reallocated array with new size %lu\n", a->size);
    }

    a->array[a->used++] = data;

}

void freeArray(Array *a) {
    free(a->array);
    a->size = 0;
    a->used = 0;
}