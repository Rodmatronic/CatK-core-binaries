// more.c - Simple more utility
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINES_PER_PAGE 24

void display(FILE *fp) {
    char buffer[4096];
    int lines = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        fputs(buffer, stdout);
        lines++;

        if (lines >= LINES_PER_PAGE) {
            printf("--More--");
            int c = getchar();
            if (c == 'q') {
                break;
            }
            lines = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp = NULL;

    if (argc == 1) {
        if (isatty(fileno(stdin))) {
            printf("Usage: %s <file>\n", argv[0]);
            return 1;
        } else {
            fp = stdin;
        }
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("fopen");
            return 1;
        }
    }

    display(fp);

    if (fp != stdin) {
        fclose(fp);
    }

    return 0;
}
