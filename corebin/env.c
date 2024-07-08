
// env - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>

extern char **environ;

int main() {
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}