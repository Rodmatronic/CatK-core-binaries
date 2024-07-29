
// yes - CatK system binary
// Written by Rodmatronics

#include <stdio.h>

int main(int argc, char *argv[]) {
    const char *message = "y";
    if (argc > 1) {
        message = argv[1];
    }
    while (1) {
        printf("%s\n", message);
        fflush(stdout);  // Ensure the output is immediately flushed
    }
    return 0;
}
