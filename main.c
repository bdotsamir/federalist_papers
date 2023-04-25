// REFERENCES:
// [1]: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// [2]: https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/#
// [3]: https://www.geeksforgeeks.org/how-to-input-or-read-a-character-word-and-a-sentence-from-user-in-c/#

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

int main(void) {
    FILE *federalist = fopen("./assets/Federalist1.txt", "r");
    if(federalist == NULL) {
        fprintf(stderr, "No such file\n");
        exit(1);
    }

    FILE *result = fopen("./result.bin", "ab");
    if(result == NULL) {
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

    // Start the scan!
    while(fscanf(federalist, "%s", BUF) == 1) {
//        printf("%i BUF %s \n", currentSentenceWordCount, BUF);

        // If we come across the author declaration in this Federalist paper, set the corresponding variables.
        if(strncmp(BUF, "Author", strlen("Author")) == 0) {
            fscanf(federalist, "%s %s", author.firstname, author.lastname);
            printf("Author: %s %s\n", author.firstname, author.lastname);
        }

        // If the buffer (the word) ends with a '.', we know we've reached the end of the sentence.
        if(endsWith(BUF, '.', strlen(BUF)) == 1) {
//            fprintf(stderr, "[DEBUG] New sentence! Previous sentence length: %i words\n\n", currentSentenceWordCount)
            // Push the current sentence word count onto the dynamic array we defined earlier
            push(&sentenceLengthArray, currentSentenceWordCount);
            // then reset the count
            currentSentenceWordCount = 0;
        }

        char *parsedWord = parsenstr(BUF, strlen(BUF));
        int wordLength = (int) strlen(parsedWord);
        push(&wordLengthArray, wordLength);
        currentSentenceWordCount++;
        free(parsedWord);
    }

    printf("\nAverage word length: %f characters\n", average(&wordLengthArray));
    printf("Average sentence word length: %f words\n", average(&sentenceLengthArray));

    freeArray(&wordLengthArray);
    freeArray(&sentenceLengthArray);

    fclose(federalist);
    return 0;
}

float average(Array *a) {
    int sum = 0;
    for(int i = 0; i < a->used; i++) {
        sum += a->array[i];
    }
    float avg = (float) sum / (float) a->used;
    return avg;
}

int endsWith(const char *src, char c, size_t n) {
    return src[n - 1] == c ? 1 : 0;
}

char *parsenstr(const char *string, size_t n) {
    char *out = calloc(n, sizeof(char));
    if(out == NULL) {
        fprintf(stderr, "Failed to allocate and initialize memory of size %lu\n", n * sizeof(char));
        exit(1);
    }

    int idx = 0;
    for(int i = 0; i < (int) n; i++) {
        char c = toupper(string[i]);
        if((c >= 48 && c <= 57) || (c >= 65 && c <= 90)) { // 0-9, A-Z
            out[idx++] = c;
        } // REF: [1]
    }

    // ... then shrink it down to the size of the valid characters.
    char *p = reallocarray(out, idx + 1, sizeof(char));
    if(!p) {
        fprintf(stderr, "Error: Failed to shrink array to size %i\n", idx + 1);
        exit(EXIT_FAILURE);
    }

    return out;
}