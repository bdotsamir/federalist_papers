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

BinaryTree *create_binary_node(char *string) {
    assert(string != NULL);

    size_t len = strlen(string);
    char *p = calloc(len + 1, sizeof(char));
    assert(p != NULL);
    strncpy(p, string, len);

    BinaryTree *newNode = malloc(sizeof(BinaryTree));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = p;
    return newNode;
}

BinaryTree *insert_in_tree(BinaryTree *root, char *string) {
    assert(string != NULL);

    //searching for the place to insert
    if (root == NULL)
        return create_binary_node(string);
    else if (strcmp(string, root->data) < 1)
        root->left = insert_in_tree(root->left, string);
    else // value is smaller should be inserted to left
        root->right = insert_in_tree(root->right, string);
    return root;
}

char *previousString = NULL;
int totalWords = 0;

void print_to_file(BinaryTree *root, FILE *outputFile, int totalWordsInThisFile) {
    if (root == NULL) return;

    // wow this is a massive shit on performance,
    // especially because this function is recursive.
    if (previousString == NULL) {
        char *p = calloc(5, sizeof(char));
        assert(p != NULL);
        previousString = p;
    } else {
        free(previousString);
        char *p = calloc(5, sizeof(char));
        assert(p != NULL);
        previousString = p;
    }

    totalWords++;

    print_to_file(root->left, outputFile, totalWordsInThisFile);
    if (strcmp(previousString, root->data) != 0) {
        strcpy(previousString, root->data);
        if (strlen(previousString) != 0) {
            printf("prev word: %s, prev count %i\n", previousString, totalWords);
            fprintf(outputFile, "%s %i %.3f\n",
                    previousString, totalWords, ((float) totalWords / (float) totalWordsInThisFile) * 1000);

            totalWords = 0;
        }
    }
    print_to_file(root->right, outputFile, totalWordsInThisFile);

}