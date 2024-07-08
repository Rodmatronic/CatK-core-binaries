
// sleep - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("sleep: usage: %s seconds\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);
    if (seconds <= 0) {
        printf("sleep: error: seconds must be a positive integer\n");
        return 1;
    }

    sleep(seconds);

    return 0;
}
