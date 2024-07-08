
// kill - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int quiet = 0;
int pid = 0;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("kill: usage: %s [ -q | <pid>]\n", argv[0]);
        return -1;
    }

    if (strcmp(argv[1], "-q") == 0) {
        quiet = 1;
        pid = atoi(argv[2]);
    } else {
        pid = atoi(argv[1]);
    }

    if (kill(pid, SIGKILL) == -1) {
        if (!quiet) {
            printf("Failed to kill PID %d\n", pid);
        }
        return -1;
    }

    if (!quiet) {
        printf("Killed PID %d\n", pid);
    }

    return 0;
}