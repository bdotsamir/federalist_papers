//
// Created by samir on 4/25/23.
//

#ifndef FEDERALIST_PAPERS_MAIN_H
#define FEDERALIST_PAPERS_MAIN_H

#endif //FEDERALIST_PAPERS_MAIN_H

#include "util/IntArray.h"
#include "util/BinaryTree.h"

typedef struct {
    char first_name[20];
    char last_name[20];
} Author;

typedef struct {
    Author author;
    float avg_word_length;
    float avg_sentence_length;
    BinaryTree *filler_words;
    int total_words;
} FederalistPaper;
