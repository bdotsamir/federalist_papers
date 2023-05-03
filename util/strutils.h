//
// Created by samir on 4/26/23.
//

#ifndef FEDERALIST_PAPERS_STRUTILS_H
#define FEDERALIST_PAPERS_STRUTILS_H

#endif //FEDERALIST_PAPERS_STRUTILS_H

#include <stdlib.h>

/**
 * Tests if a string contains a "filler" word
 * @param src Source string to test
 * @param n Length of string
 * @return 1 = true; 0 = false
 */
int is_filler_word(const char *src, size_t n);

/**
 * Find if a given src string of n ends with c
 * @param src Source string
 * @param c Character to test
 * @param n Length of string
 * @return 1 = true; 0 = false
 */
int ends_with(const char *src, char c, size_t n);

/**
 * Parse a string so that only A-Z and 0-9 are accepted, case insensitive
 * @param string Source string to parse
 * @param n Length of the source string
 * @return New string containing only the valid characters (in all uppercase)
 */
char *parsenstr(const char *string, size_t n);