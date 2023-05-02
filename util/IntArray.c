// REFERENCES:
// [1]: https://clang.llvm.org/extra/clang-tidy/checks/bugprone/suspicious-realloc-usage.html
// [2]: https://stackoverflow.com/a/3536261/8916706

// This entire file is pretty much courtesy of REF: [2].
// Use this "class" when you need to construct an integer array, but you don't reasonably know
// how long the array is going to be until runtime.

/* The way this functions is entirely driven by the `push` function. When the user calls IntArray_push
   with the data to add onto the array, it checks to see if the array's size is equal to the
   amount of used elements. If it is, it then reallocates the memory to be twice its previous
   size, and adds the requested data onto the array. */
// Each function has been described using jsdoc-style comments in the array.h file.

#include <stdlib.h>
#include <stdio.h>
#include "IntArray.h"

void IntArray_init(IntArray *a, size_t initialSize) {
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

void IntArray_push(IntArray *a, int data) {
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

void IntArray_free(IntArray *a) {
    free(a->array);
    a->array = NULL;
    a->size = 0;
    a->used = 0;
}

float IntArray_average(IntArray *a) {
    int sum = 0;
    for (int i = 0; i < a->used; i++) {
        sum += a->array[i];
    }
    float avg = (float) sum / (float) a->used;
    return avg;
}
