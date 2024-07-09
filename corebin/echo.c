
// echo - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define VERSION "1.0 CatK-echo"

int newline = 1;
int interpret_backslash = 0;  // Flag to interpret escape sequences (not implemented yet)

int write_to_file(const char *filename, const char *content, int append) {
    int fd;
    if (append) {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (fd < 0) {
        printf("echo: no such file or directory\n");
        return -1;
    }

    if (write(fd, content, strlen(content)) < 0) {
        printf("echo: failed to write to specified file\n");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\n"); // ECHO normally prints a newline even when run without args
        return 0;
    }

    if (strcmp(argv[1], "-V") == 0) {
        printf("echo: version: %s\n", VERSION);
        return 0;
    }

    int redirect_index = 0;
    int append = 0;

    // Detect redirection
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0) {
            redirect_index = i;
            if (strcmp(argv[i], ">>") == 0) {
                append = 1;
            }
            break;
        }
    }

    // Calculate the length of the output string
    size_t output_length = 0;
    for (int i = 1; i < (redirect_index ? redirect_index : argc); i++) {
        output_length += strlen(argv[i]) + 1;
    }

    char *output = malloc(output_length + (newline ? 1 : 0));
    if (!output) {
        printf("echo: malloc operation failed");
        return -1;
    }

    output[0] = '\0';

    // Loop through each argument starting from the second
    for (int i = 1; i < (redirect_index ? redirect_index : argc); i++) {
        if (strcmp(argv[i], "-n") == 0) {
            newline = 0;
        } else if (strcmp(argv[i], "-e") == 0) {
            interpret_backslash = 1;
        } else {
            strcat(output, argv[i]);
            if (i < (redirect_index ? redirect_index : argc) - 1) {
                strcat(output, " ");
            }
        }
    }

    if (newline) {
        strcat(output, "\n");
    }

    if (redirect_index) {
        if (redirect_index + 1 >= argc) {
            printf("echo: missing file operand after '%s'\n", argv[redirect_index]);
            free(output);
            return 0;
        }
        write_to_file(argv[redirect_index + 1], output, append);
    } else {
        printf("%s", output);
    }

    free(output);
    return 0;
}
