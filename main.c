// REFERENCES:
// [1]: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// [2]: https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/#

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *federalist = fopen("./assets/Federalist1.txt", "r");
    if(federalist == NULL) {
        fprintf(stderr, "No such file\n");
        exit(1);
    }

    char BUF[256];

    char authorFirstName[20], authorLastName[20];
    while(fscanf(federalist, "%s", BUF) == 1) {
        if(strncmp(BUF, "Author", 6) == 0) {
            fscanf(federalist, "%s %s", authorFirstName, authorLastName);
            printf("Author: %s %s\n", authorFirstName, authorLastName);
            break;
        }
//        printf("%s ", BUF);
    }

    fclose(federalist);
    return 0;
}
