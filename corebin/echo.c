
// echo - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <string.h>

#define VERSION "1.0 CatK-echo"

int newline = 1;
int interpret_backslash = 0;  // Flag to interpret escape sequences (not implemented yet)

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\n"); // ECHO normally prints a newline even when run without args
        return 1;
    }

    if (strcmp(argv[1], "-V") == 0) {
        printf("echo: version: %s\n", VERSION);
        return 0;
    }

    // Loop through each argument starting from the second
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            newline = 0;
        } else if (strcmp(argv[i], "-e") == 0) {
            interpret_backslash = 1;
        } else {
            printf("%s", argv[i]);
        }
    }

    if (newline) {
        printf("\n");
    }

    return 0;
}
