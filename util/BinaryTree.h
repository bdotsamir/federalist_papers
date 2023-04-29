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

BinaryTree *createBinaryNode(char *string);
BinaryTree *insertInTree(BinaryTree *root, char *string);
int searchTree(BinaryTree *root, char *string);
void printinorder(BinaryTree *root);