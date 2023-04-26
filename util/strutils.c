//
// Created by samir on 4/26/23.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "strutils.h"

char fillerWords[][5] = {"of", "the", "by", "from", "to", "a", "an", "and", "for", "than"};
int isFillerWord(const char *src, size_t n) {
    // Create a copy of src, so we can lowercase-ify all of it
    char *p = calloc(n, sizeof(char));
    if(!p) {
        fprintf(stderr, "Failed to allocate temporary memory for isFillerWord\n");
        exit(EXIT_FAILURE);
    }
    strncpy(p, src, n);
    // actually perform the lowercase-ification
    for(int i = 0; i < n; i++) {
        p[i] = tolower(p[i]);
    }

    int result = 0;
    for(int i = 0; i < floor(sizeof(fillerWords) / sizeof(fillerWords[0])); i++) {
        if(strncmp(p, fillerWords[i], n) == 0) {
            result = 1;
        }
    }

    free(p);

    return result;
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