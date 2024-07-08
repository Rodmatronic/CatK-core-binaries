
// usleep - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usleep: usage: %s milliseconds\n", argv[0]);
        return 1;
    }

    int mils = atoi(argv[1]);
    if (mils <= 0) {
        printf("usleep: error: milliseconds must be a positive integer\n");
        return 1;
    }

    usleep(mils);

    return 0;
}
