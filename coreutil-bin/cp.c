
// cp - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

int copy_file(const char *src, const char *dest) {
    int src_fd, dest_fd;
    char buffer[4096];
    ssize_t bytes_read;

    src_fd = open(src, O_RDONLY);
    if (src_fd < 0) {
        printf("cp: no such file or directory\n");
        return -1;
    }

    dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        printf("cp: failed to open file\n");
        close(src_fd);
        return -1;
    }

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            printf("cp: failed to write file\n");
            close(src_fd);
            close(dest_fd);
            return -1;
        }
    }

    close(src_fd);
    close(dest_fd);
    return 0;
}

int copy_directory(const char *src, const char *dest) {
    struct stat st;
    DIR *dir;
    struct dirent *entry;
    char src_path[4096], dest_path[4096];

    if (stat(dest, &st) == -1) {
        mkdir(dest, 0755);
    }

    dir = opendir(src);
    if (!dir) {
        printf("cp: failed to open directory\n");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, entry->d_name);

        if (entry->d_type == DT_DIR) {
            copy_directory(src_path, dest_path);
        } else {
            copy_file(src_path, dest_path);
        }
    }

    closedir(dir);
    return 0;
}

int main(int argc, char *argv[]) {
    int recursive = 0;
    char *src = NULL, *dest = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            recursive = 1;
        } else if (src == NULL) {
            src = argv[i];
        } else if (dest == NULL) {
            dest = argv[i];
        }
    }

    if (src == NULL || dest == NULL) {
        printf("Usage: %s [-r] <source> <destination>\n", argv[0]);
        return -1;
    }

    struct stat st;
    if (stat(src, &st) == -1) {
        printf("cp: failed to stat file/directory\n");
        return -1;
    }

    if (S_ISDIR(st.st_mode)) {
        if (!recursive) {
            printf("cp: -r not specified; omitting directory '%s'\n", src);
            return -1;
        }
        copy_directory(src, dest);
    } else {
        copy_file(src, dest);
    }

    return 0;
}
