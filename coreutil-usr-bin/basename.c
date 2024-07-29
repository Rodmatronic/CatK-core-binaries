
// basename - CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return -1;
    }
    char *path = strdup(argv[1]);
    printf("%s\n", basename(path));
    free(path);
    return 0;
}
