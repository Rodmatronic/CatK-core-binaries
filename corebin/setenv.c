
// setenv - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("setenv: usage: %s VARIABLE VALUE\n", argv[0]);
        return -1;
    }

    const char *variable = argv[1];
    const char *value = argv[2];

    if (setenv(variable, value, 1) != 0) {
        printf("Failed to set ENV\n");
        return 1;
    }

    printf("setenv: Environment variable %s set to %s\n", variable, value);
    return 0;
}
