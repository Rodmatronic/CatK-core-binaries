
// poweroff - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Function to sleep for a specified amount of time
void sleep_for_time(int seconds) {
    printf("poweroff: System will go down in %d seconds...\n", seconds);
    sleep(seconds);
}

int main(int argc, char *argv[]) {
    int opt;
    int sleep_time = 0;
    int operation = 0; // 1 for reboot, 2 for shutdown, 3 for halt

    while ((opt = getopt(argc, argv, "rsht:")) != -1) {
        switch (opt) {
            case 'r':
                operation = 1;
                break;
            case 's':
                operation = 2;
                break;
            case 'h':
                operation = 3;
                break;
            case 't':
                sleep_time = atoi(optarg);
                break;
            default:
                printf("Usage: %s [-r] [-s] [-h] [-t seconds]\n", argv[0]);
                return -1;
        }
    }

    if (sleep_time > 0) {
        sleep_for_time(sleep_time);
    }

    switch (operation) {
        case 1:
            printf("poweroff: reboot issued to kernel\nSYSTEM IS GOING DOWN NOW!!\n");
            if (system("reboot") == -1) {
                printf("poweroff: Failed to reboot");
                return -1;
            }
            break;
        case 2:
            printf("poweroff: shutdown issued to kernel\nSYSTEM IS GOING DOWN NOW!!\n");
            if (system("shutdown now") == -1) {
                printf("poweroff: Failed to shutdown");
                return -1;
            }
            break;
        case 3:
            printf("poweroff: halt issued to kernel\nSYSTEM IS GOING DOWN NOW!!\n");
            if (system("halt") == -1) {
                perror("poweroff: Failed to halt");
                return -1;
            }
            break;
        default:
            printf("poweroff: no arguments, poweroff issued to kernel\nSYSTEM IS GOING DOWN NOW!!\n");
            if (system("shutdown") == -1) {
                perror("poweroff: Failed to poweroff");
                return -1;
            }
    }

    return 0;
}
