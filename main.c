// REFERENCES:
// [1]: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// [2]: https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/#
// [3]: https://www.geeksforgeeks.org/how-to-input-or-read-a-character-word-and-a-sentence-from-user-in-c/#

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "util/strutils.h"
#include "util/BinaryTree.h"

int main(void) {
    FILE *federalist = fopen("./assets/Federalist1.txt", "r");
    if (federalist == NULL) {
        fprintf(stderr, "No such file\n");
        exit(1);
    }

    FILE *result = fopen("./result.txt", "a");
    if (result == NULL) {
        fprintf(stderr, "Failed to open result file\n");
        exit(1);
    }

    // Create a buffer to hold the strings we scan in
    char BUF[256];

    // Create a dynamic array that holds the lengths of each word
    IntArray wordLengthArray;
    IntArray_init(&wordLengthArray, 8);

    // Create a dynamic array that holds the lengths of each sentence
    IntArray sentenceLengthArray;
    IntArray_init(&sentenceLengthArray, 8);

    Author author;

    // Create local variable that will keep track of the number of words in the current sentence.
    // This variable is reset to zero every time we encounter a "."
    int current_sentence_word_count = 0;

    int filler_words = 0;

    BinaryTree *root_binary_node;

    int total_words_in_this_paper = 0;

    // Start the scan!
    while (fscanf(federalist, "%s", BUF) == 1) {
        total_words_in_this_paper++;
//        printf("%i BUF %s \n", current_sentence_word_count, BUF);

        // If we come across the author declaration in this Federalist paper, set the corresponding variables.
        if (strncmp(BUF, "Author", strlen("Author")) == 0) {
            fscanf(federalist, "%s %s", author.first_name, author.last_name);
            printf("Author: %s %s\n", author.first_name, author.last_name);
        }

        // If the buffer (the word) ends with a '.', we know we've reached the end of the sentence.
        if (ends_with(BUF, '.', strlen(BUF)) == 1) {
//            fprintf(stderr, "[DEBUG] New sentence! Previous sentence length: %i words\n\n", current_sentence_word_count)
            // Push the current sentence word count onto the dynamic array we defined earlier
            IntArray_push(&sentenceLengthArray, current_sentence_word_count);
            // then reset the count
            current_sentence_word_count = 0;
        }

        // Actually parse out the characters we want
        char *parsedWord = parsenstr(BUF, strlen(BUF));
        int wordLength = (int) strlen(parsedWord);
        IntArray_push(&wordLengthArray, wordLength);
        current_sentence_word_count++;

        int isFiller = is_filler_word(parsedWord, strlen(parsedWord));
        if (isFiller == 1) {
            BinaryTree *currentBinaryNode = insert_in_tree(root_binary_node, parsedWord);
            root_binary_node = currentBinaryNode;

            filler_words++;
        }

        // then free up the parsedWord memory since it's dynamically allocated
        free(parsedWord);
    }

    printf("\nAverage word length: %.3f characters\n", IntArray_average(&wordLengthArray));
    printf("Average sentence word length: %.3f words\n", IntArray_average(&sentenceLengthArray));
    printf("Total filler words: %i\n", filler_words);

    fprintf(result, "================================\n\n");
    fprintf(result, "FILE %s:\n", path);
    fprintf(result, "Author: %s %s\n\n", author.first_name, author.last_name);
    fprintf(result, "Filler Word | Times Used | Out of 1000\n");
    print_to_file(root_binary_node, result, total_words_in_this_paper);
    fprintf(result, "\n");
    fprintf(result, "Total words in this paper: %i\n", total_words_in_this_paper);
    fprintf(result, "Average word length: %.3f\n", IntArray_average(&wordLengthArray));
    fprintf(result, "Average sentence length: %.3f\n", IntArray_average(&sentenceLengthArray));
    fprintf(result, "\n================================\n\n");

    IntArray_free(&wordLengthArray);
    IntArray_free(&sentenceLengthArray);

    fclose(federalist);
    fclose(result);
    return 0;
}
