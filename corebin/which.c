
// which - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void which(const char *program) {
    char *path = getenv("PATH");
    if (path == NULL) {
        printf("which: PATH environment variable not found\n");
        return;
    }

    char *dir = strtok(path, ":");
    while (dir != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, program);
        if (access(full_path, X_OK) == 0) {
            printf("%s\n", full_path);
            return;
        }
        dir = strtok(NULL, ":");
    }

    printf("%s not found\n", program);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <program>\n", argv[0]);
        return -1;
    }

    which(argv[1]);
    return 0;
}
