
// ls - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define VERSION "1.0 CatK-ls"

void list_directory(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        printf("ls: failed to open file\n");
        return;
    }

    while ((entry = readdir(dp))) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    char *path;

    if (argc < 2) {
        // No arguments provided, use current working directory
        path = getenv("PWD");
        if (path == NULL) {
            printf("ls: failed to get PWD env variable\n");
            return -1;
        }
    } else if (strcmp(argv[1], "-V") == 0) {
        // Version option
        printf("ls: version: %s\n", VERSION);
        return 0;
    } else {
        // Use provided path argument
        path = argv[1];
    }

    list_directory(path);

    return 0;
}
