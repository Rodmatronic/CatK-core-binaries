
// clear - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>

int main() {
    // ANSI escape sequence to clear the terminal
    printf("\033[H\033[J");
    return 0;
}