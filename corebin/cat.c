
// cat - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>

int cat_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("cat: no such file or directory\n");
        return -1;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, stdout) != bytes_read) {
            printf("cat: I/O error\n");
            fclose(file);
            return -1;
        }
    }

    if (ferror(file)) {
        printf("cat: failed to read file\n");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> [file2 ...]\n", argv[0]);
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        cat_file(argv[i]);
    }

    return 0;
}