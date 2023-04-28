//
// Created by samir on 4/27/23.
//

#ifndef FEDERALIST_PAPERS_LINKEDLIST_H
#define FEDERALIST_PAPERS_LINKEDLIST_H

#endif //FEDERALIST_PAPERS_LINKEDLIST_H

/**
 * This is a doubly-linked-list structure. This particular implementation
 * is special, in that the contents are dynamic-length character arrays.
 */
typedef struct DLLNode {
    struct DLLNode *next;
    struct DLLNode *prev;
    char *data;
} DLLNode;

/**
 * Create a new node, and edit the nodes around it if necessary
 * @param node Previous node, if necessary, otherwise NULL
 * @param data Character array to put into this node
 * @return Pointer to the new node that's been created
 */
DLLNode *newNode(DLLNode *node, char *data);

/**
 * Delete a node, editing the surrounding nodes if necessary
 * @param node The node to delete
 */
void delNode(DLLNode *node);

/**
 * Edit the character array within a specified node
 * @param node The node in question
 * @param newData The new character array
 */
void editNode(DLLNode *node, char *newData);

/**
 * Get the head node from anywhere in the list.
 * If your chain is long, you should compute this early in the execution and cache the
 * result for better performance.
 * @param node Entrypoint node
 * @return Pointer to the head node
 */
DLLNode *getHead(DLLNode *node);