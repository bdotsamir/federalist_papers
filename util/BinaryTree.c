//
// Created by samir on 4/28/23.
//

// Thank you,
// https://www.scaler.com/topics/binary-tree-in-c/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "BinaryTree.h"

BinaryTree *createBinaryNode(char *string) {
    assert(string != NULL);

    char *p = calloc(strlen(string), sizeof(char));
    assert(p != NULL);
    strcpy(p, string);

    BinaryTree *newNode = malloc(sizeof(BinaryTree));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = p;
    return newNode;
}

BinaryTree *insertInTree(BinaryTree *root, char *string) {
    assert(string != NULL);

    //searching for the place to insert
    if(root == NULL)
        return createBinaryNode(string);
    else if(strcmp(string, root->data) < 1)
        root->left = insertInTree(root->left, string);
    else // value is smaller should be inserted to left
        root->right = insertInTree(root->right,string);
    return root;
}

int searchTree(BinaryTree *root, char *string) {
    if(strcmp(root->data, string) == 0) {
        return 1;
    } else {
        if(root->left != NULL)
            return searchTree(root->left, string);
        else if(root->right != NULL)
            return searchTree(root->right, string);
        else
            return 0;
    }
}

void printinorder(BinaryTree *root) {
    if(root == NULL) return;

    printinorder(root->left);
    printf(" %s ", root->data);
    printinorder(root->right);
}
