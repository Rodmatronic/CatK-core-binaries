
// mv - core CatK system utility
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void print_usage(const char *prog_name) {
    printf("Usage: %s <source> <destination>\n", prog_name);
}

int copy_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    if (src == NULL) {
        printf("mv: no such file or directory\n");
        return -1;
    }

    FILE *dest = fopen(destination, "wb");
    if (dest == NULL) {
        printf("mv: no such file or directory\n");
        fclose(src);
        return -1;
    }

    char buffer[4096];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            printf("mv: cannot access file\n");
            fclose(src);
            fclose(dest);
            return -1;
        }
    }

    fclose(src);
    fclose(dest);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage(argv[0]);
        return -1;
    }

    const char *source = argv[1];
    const char *destination = argv[2];

    // Check if destination is a directory
    struct stat dest_stat;
    if (stat(destination, &dest_stat) == 0 && S_ISDIR(dest_stat.st_mode)) {
        // Construct new destination path
        char *dest_path = malloc(strlen(destination) + strlen(source) + 2);
        if (dest_path == NULL) {
            printf("mv: no such file or directory\n");
            return -1;
        }
        sprintf(dest_path, "%s/%s", destination, strrchr(source, '/') ? strrchr(source, '/') + 1 : source);
        destination = dest_path;
    }

    // Attempt to rename the file
    if (rename(source, destination) != 0) {
        if (copy_file(source, destination) != 0) {
            printf("mv: failed to copy file\n");
            free((void *)destination);
            return -1;
        }
        // Remove the source file after copying
        if (remove(source) != 0) {
            perror("remove");
            free((void *)destination);
            return -1;
        }
    } else {
        printf("mv: cannot rename file\n");
        if (dest_stat.st_mode & S_IFDIR) {
            free((void *)destination);
        }
        return 1;
    }

    if (dest_stat.st_mode & S_IFDIR) {
        free((void *)destination);
    }

    return 0;
}
