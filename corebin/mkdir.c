
// mkdir - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <directory1> [directory2 ...]\n", argv[0]);
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        if (mkdir(argv[i], 0755) != 0) {
            printf("mkdir: no such file or directory\n");
            return -1;
        }
    }

    return 0;
}