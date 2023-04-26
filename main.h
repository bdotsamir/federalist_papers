//
// Created by samir on 4/25/23.
//

#ifndef FEDERALIST_PAPERS_MAIN_H
#define FEDERALIST_PAPERS_MAIN_H

#endif //FEDERALIST_PAPERS_MAIN_H

#include "util/array.h"

typedef struct {
    char firstname[20];
    char lastname[20];
} Author;

typedef struct {
    Author author;
    float avgWordLength;
    float avgSentenceLength;
    float avgFillerWords;
} FederalistPaper;

/**
 * Find the average of a given Array struct
 * @param a Pointer to an Array struct
 * @return The average
 */
float average(Array *a);
