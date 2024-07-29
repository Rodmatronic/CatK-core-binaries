
// realpath - CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return -1;
    }
    char resolved_path[PATH_MAX];
    if (!realpath(argv[1], resolved_path)) {
        printf("realpath: No such file or directory\n");
        return -1;
    }
    printf("%s\n", resolved_path);
    return 0;
}
