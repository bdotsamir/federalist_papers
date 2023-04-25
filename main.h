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

/**
 * Find if a given src string of n ends with c
 * @param src Source string
 * @param c Character to test
 * @param n Length of string
 * @return 1 = true; 0 = false
 */
int endsWith(const char *src, char c, size_t n);

/**
 * Parse a string so that only A-Z and 0-9 are accepted, case insensitive
 * @param string Source string to parse
 * @param n Length of the source string
 * @return New string containing only the valid characters (in all uppercase)
 */
char *parsenstr(const char *string, size_t n);