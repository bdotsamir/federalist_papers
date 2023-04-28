//
// Created by samir on 4/25/23.
//

#ifndef FEDERALIST_PAPERS_MAIN_H
#define FEDERALIST_PAPERS_MAIN_H

#endif //FEDERALIST_PAPERS_MAIN_H

#include "util/IntArray.h"

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
