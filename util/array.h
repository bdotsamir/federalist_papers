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
} Array;

/**
 * Initialize a new, empty array
 * @param a Array structure pointer
 * @param initialSize Initial size of the array
 */
void initArray(Array *a, size_t initialSize);

/**
 * Push a new element onto the array, automatically reallocating if necessary
 * @param a Array structure pointer
 * @param data Integer data to push
 */
void push(Array *a, int data);

/**
 * Free the memory used by the array
 * @param a Array structure pointer
 */
void freeArray(Array *a);