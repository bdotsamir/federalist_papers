// REFERENCES:
// [1]: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// [2]: https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/#
// [3]: https://www.geeksforgeeks.org/how-to-input-or-read-a-character-word-and-a-sentence-from-user-in-c/#

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include "main.h"
#include "util/strutils.h"

FederalistPaper parse_federalist(FILE *file);

int main(void) {

    FILE *output_file = fopen("./output_file.txt", "w");
    assert(output_file != NULL);

    // Open the assets folder, which contains all the federalist papers
    DIR *federalist_papers_folder = opendir("./assets");
    assert(federalist_papers_folder != NULL);

    // Get the file info (file name, namely)
    struct dirent *file_info;
    // Loop through all the files in the assets/ directory
    while ((file_info = readdir(federalist_papers_folder))) {
        // If the file name is the current directory or the previous directory, skip this iteration
        if (strcmp(file_info->d_name, ".") == 0 || strcmp(file_info->d_name, "..") == 0) {
            continue;
        }

        if(strcmp(file_info->d_name, "Federalist63.txt") == 0) {
            fprintf(stderr, "[WARNING] Federalist 63 encountered. It will not have an author.\n");
            continue;
        }

        // Actually open the federalist paper file
        char assets[] = "./assets/";
        char *full_file_path = strncat(assets, file_info->d_name, strlen(file_info->d_name));

        printf("%s\n", full_file_path);
        FILE *federalist = fopen(full_file_path, "r");
        if(!federalist) {
            fprintf(stderr, "Error opening file with name %s\n", full_file_path);
            exit(1);
        }

        // Parse out the information from the paper
        FederalistPaper parsed_paper = parse_federalist(federalist);

        fprintf(output_file, "File: %s\n", full_file_path);
        fprintf(output_file, "Filler Word | Times Used | Out of 1000\n");
        print_to_file(parsed_paper.filler_words, output_file, parsed_paper.total_words);
        fprintf(output_file, "\n\n");

        // Then close the paper since we don't need it much anymore.
        fclose(federalist);
    }

    fclose(output_file);
    closedir(federalist_papers_folder);
    return 0;
}

FederalistPaper parse_federalist(FILE *file) {
    FederalistPaper federalist;

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

    BinaryTree *root_binary_node = NULL;

    int total_words_in_this_paper = 0;

    // Start the scan!
    while (fscanf(file, "%s", BUF) == 1) {
        total_words_in_this_paper++;
//        printf("%i BUF %s \n", current_sentence_word_count, BUF);

        // If we come across the author declaration in this Federalist paper, set the corresponding variables.
        if (strncmp(BUF, "Author", strlen("Author")) == 0) {
            fscanf(file, "%s %s", author.first_name, author.last_name);
//            printf("Author: %s %s\n", author.first_name, author.last_name);
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
        char *parsedWord = calloc(strlen(BUF), sizeof(char));
        parsenstr(BUF, strlen(BUF), parsedWord);
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

//    printf("\nAverage word length: %.3f characters\n", IntArray_average(&wordLengthArray));
//    printf("Average sentence word length: %.3f words\n", IntArray_average(&sentenceLengthArray));
//    printf("Total filler words: %i\n", filler_words);

    federalist.author = author;
    federalist.avg_word_length = IntArray_average(&wordLengthArray);
    federalist.avg_sentence_length = IntArray_average(&sentenceLengthArray);
    federalist.total_words = total_words_in_this_paper;
    federalist.filler_words = root_binary_node;

    IntArray_free(&wordLengthArray);
    IntArray_free(&sentenceLengthArray);

    return federalist;
}