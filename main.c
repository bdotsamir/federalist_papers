// REFERENCES:
// [1]: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// [2]: https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/#
// [3]: https://www.geeksforgeeks.org/how-to-input-or-read-a-character-word-and-a-sentence-from-user-in-c/#

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    char BUF[256];
    Array wordLengthArray;
    initArray(&wordLengthArray, 8);

    Array sentenceLengthArray;
    initArray(&sentenceLengthArray, 8);

    Author author;

    int currentSentenceWordCount = 0;
    while(fscanf(federalist, "%s", BUF) == 1) {
//        printf("%i BUF %s \n", currentSentenceWordCount, BUF);
        // If we come across the author declaration in this Federalist paper, set the corresponding variables.
        if(strncmp(BUF, "Author", strlen("Author")) == 0) {
            fscanf(federalist, "%s %s", author.firstname, author.lastname);
            printf("Author: %s %s\n", author.firstname, author.lastname);
        }

        if(endsWith(BUF, '.', strlen(BUF)) == 1) {
//            fprintf(stderr, "[DEBUG] New sentence! Previous sentence length: %i words\n\n", currentSentenceWordCount);
            push(&sentenceLengthArray, currentSentenceWordCount);
            currentSentenceWordCount = 0;
        }

        int wordLength = (int) strlen(BUF);
        push(&wordLengthArray, wordLength);
        currentSentenceWordCount++;
    }

    printf("\nAverage word length: %f characters\n", average(&wordLengthArray));
    printf("Average sentence word length: %f words\n", average(&sentenceLengthArray));

    freeArray(&wordLengthArray);

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