// REFERENCES:
// [1]: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// [2]: https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/#
// [3]: https://www.geeksforgeeks.org/how-to-input-or-read-a-character-word-and-a-sentence-from-user-in-c/#

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "util/strutils.h"

int main(void) {
    FILE *federalist = fopen("./assets/Federalist1.txt", "r");
    if (federalist == NULL) {
        fprintf(stderr, "No such file\n");
        exit(1);
    }

    FILE *result = fopen("./result.bin", "ab");
    if (result == NULL) {
        fprintf(stderr, "Failed to open result file\n");
        exit(1);
    }

    // Create a buffer to hold the strings we scan in
    char BUF[256];

    // Create a dynamic array that holds the lengths of each word
    Array wordLengthArray;
    initArray(&wordLengthArray, 8);

    // Create a dynamic array that holds the lengths of each sentence
    Array sentenceLengthArray;
    initArray(&sentenceLengthArray, 8);

    Author author;

    // Create local variable that will keep track of the number of words in the current sentence.
    // This variable is reset to zero every time we encounter a "."
    int currentSentenceWordCount = 0;

    int fillerWords = 0;

    // Start the scan!
    while (fscanf(federalist, "%s", BUF) == 1) {
//        printf("%i BUF %s \n", currentSentenceWordCount, BUF);

        // If we come across the author declaration in this Federalist paper, set the corresponding variables.
        if (strncmp(BUF, "Author", strlen("Author")) == 0) {
            fscanf(federalist, "%s %s", author.firstname, author.lastname);
            printf("Author: %s %s\n", author.firstname, author.lastname);
        }

        // If the buffer (the word) ends with a '.', we know we've reached the end of the sentence.
        if (endsWith(BUF, '.', strlen(BUF)) == 1) {
//            fprintf(stderr, "[DEBUG] New sentence! Previous sentence length: %i words\n\n", currentSentenceWordCount)
            // Push the current sentence word count onto the dynamic array we defined earlier
            push(&sentenceLengthArray, currentSentenceWordCount);
            // then reset the count
            currentSentenceWordCount = 0;
        }

        // Actually parse out the characters we want
        char *parsedWord = parsenstr(BUF, strlen(BUF));
        int wordLength = (int) strlen(parsedWord);
        push(&wordLengthArray, wordLength);
        currentSentenceWordCount++;

        int isFiller = isFillerWord(parsedWord, strlen(parsedWord));
        if (isFiller == 1)
            fillerWords++;

        // then free up the parsedWord memory since it's dynamically allocated
        free(parsedWord);
    }

    printf("\nAverage word length: %f characters\n", average(&wordLengthArray));
    printf("Average sentence word length: %f words\n", average(&sentenceLengthArray));
    printf("Total filler words: %i\n", fillerWords);

    freeArray(&wordLengthArray);
    freeArray(&sentenceLengthArray);

    fclose(federalist);
    fclose(result);
    return 0;
}
