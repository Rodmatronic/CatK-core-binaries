
// kill - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <string.h>
#include <signal.h>

#define VERSION "1.0 CatK-kill"
int quiet = 0;
int pid = 0;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("kill: usage: %s [-V | -q | <pid>]\n", argv[0]);
        return -1;
    }

    if (strcmp(argv[1], "-V") == 0) {
        printf("kill: version: %s\n", VERSION);
        return 0;
    } else if (strcmp(argv[1], "-q") == 0) {
        if (argc < 3) {
            printf("kill: usage: %s [-V | -q | <pid>]\n", argv[0]);
            return -1;
        }
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