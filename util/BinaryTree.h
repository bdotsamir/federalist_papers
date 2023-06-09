//
// Created by samir on 4/28/23.
//

#ifndef FEDERALIST_PAPERS_BINARYTREE_H
#define FEDERALIST_PAPERS_BINARYTREE_H

#endif //FEDERALIST_PAPERS_BINARYTREE_H

typedef struct BinaryTree {
    struct BinaryTree *left;
    struct BinaryTree *right;
    char *data;
} BinaryTree;

BinaryTree *create_binary_node(char *string);
BinaryTree *insert_in_tree(BinaryTree *root, char *string);

void print_to_file(BinaryTree *root, FILE *outputFile, int totalWordsInThisFile);