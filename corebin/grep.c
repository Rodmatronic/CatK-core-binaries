
// grep - CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(FILE *fp, const char *pattern) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pattern> [file...]\n", argv[0]);
        return -1;
    }

    const char *pattern = argv[1];

    if (argc == 2) {
        // No file specified, read from stdin
        grep(stdin, pattern);
    } else {
        // Read from specified files
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("grep: no such file or directory");
                continue;
            }
            grep(fp, pattern);
            fclose(fp);
        }
    }

    return 0;
}