
// rm - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int remove_file(const char *path) {
    if (unlink(path) != 0) {
        printf("rm: Failed to remove file");
        return -1;
    }
    return 0;
}

int remove_directory(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    char filepath[4096];

    if (!dir) {
        printf("rm: Failed to remove the file: no such file or directory");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(filepath, &st) == -1) {
            printf("rm: Failed to remove the file/directory: no such file or directory");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            remove_directory(filepath);
        } else {
            remove_file(filepath);
        }
    }

    closedir(dir);

    if (rmdir(path) != 0) {
        printf("rm: Failed to remove the file/directory");
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int recursive = 0, force = 0;
    char *path = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            recursive = 1;
        } else if (strcmp(argv[i], "-f") == 0) {
            force = 1;
        } else {
            path = argv[i];
        }
    }

    if (path == NULL) {
        printf("rm: usage: %s [-r] [-f] <file/directory>\n", argv[0]);
        return -1;
    }

    struct stat st;
    if (stat(path, &st) == -1) {
        if (force) {
            return 0;
        }
        return -1;
    }

    if (S_ISDIR(st.st_mode)) {
        if (!recursive) {
            printf("rm: cannot remove '%s': Is a directory\n", path);
            return -1;
        }
        remove_directory(path);
    } else {
        remove_file(path);
    }

    return 0;
}