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
    if (root == NULL)
        return createBinaryNode(string);
    else if (strcmp(string, root->data) < 1)
        root->left = insertInTree(root->left, string);
    else // value is smaller should be inserted to left
        root->right = insertInTree(root->right, string);
    return root;
}

int searchTree(BinaryTree *root, char *string) {
    if (strcmp(root->data, string) == 0) {
        return 1;
    } else {
        if (root->left != NULL)
            return searchTree(root->left, string);
        else if (root->right != NULL)
            return searchTree(root->right, string);
        else
            return 0;
    }
}

void print_tree_in_order(BinaryTree *root) {
    if (root == NULL) return;

    print_tree_in_order(root->left);
    printf(" %s ", root->data);
    print_tree_in_order(root->right);
}

char *previousString;
int totalWords = 0;

void print_to_file(BinaryTree *root, FILE *outputFile, int totalWordsInThisFile) {
    if (root == NULL) return;

    // wow this is a massive shit on performance,
    // especially because this function is recursive.
    if (previousString == NULL) {
        previousString = calloc(5, sizeof(char));
    }

    totalWords++;

    print_to_file(root->left, outputFile, totalWordsInThisFile);
    if (strcmp(previousString, root->data) != 0) {
        strcpy(previousString, root->data);
        if (strlen(previousString) != 0) {
            printf("prev word: %s, prev count %i\n", previousString, totalWords);
            fprintf(outputFile, "%s %i %f\n",
                    previousString, totalWords, ((float) totalWords / (float) totalWordsInThisFile) * 1000);

            totalWords = 0;
        }
    }
    print_to_file(root->right, outputFile, totalWordsInThisFile);

}