//
// Created by samir on 4/25/23.
//

#ifndef FEDERALIST_PAPERS_ARRAY_H
#define FEDERALIST_PAPERS_ARRAY_H

#endif //FEDERALIST_PAPERS_ARRAY_H

#include <stdlib.h>

typedef struct {
    int *array;
    size_t used;
    size_t size;
} IntArray;

/**
 * Initialize a new, empty array
 * @param a IntArray structure pointer
 * @param initial_size Initial size of the array
 */
void IntArray_init(IntArray *a, size_t initial_size);

/**
 * Push a new element onto the array, automatically reallocating if necessary
 * @param a IntArray structure pointer
 * @param data Integer data to IntArray_push
 */
void IntArray_push(IntArray *a, int data);

/**
 * Free the memory used by the array
 * @param a IntArray structure pointer
 */
void IntArray_free(IntArray *a);

/**
 * Find the IntArray_average of a given IntArray struct
 * @param a Pointer to an IntArray struct
 * @return The IntArray_average
 */
float IntArray_average(IntArray *a);