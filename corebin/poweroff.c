
// poweroff - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to sleep for a specified amount of time
void sleep_for_time(int seconds) {
    printf("poweroff: System will go down in %d seconds...\n", seconds);
    sleep(seconds);
    printf("System shutdown has arrived!\n");
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
                printf("poweroff: usage: %s [-r] [-s] [-h] [-t seconds]\n", argv[0]);
                return -1;
        }
    }

    if (sleep_time > 0) {
        sleep_for_time(sleep_time);
    }

    switch (operation) {
        case 1:
            sync();
            printf("poweroff: reboot issued to kernel\nSYSTEM IS GOING DOWN NOW!!\n");
            if (system("reboot") == -1) {
                printf("poweroff: Failed to reboot");
                return -1;
            }
            break;
        case 2:
            sync();
            printf("poweroff: shutdown issued to kernel\nSYSTEM IS GOING DOWN NOW!!\n");
            if (system("shutdown now") == -1) {
                printf("poweroff: Failed to shutdown");
                return -1;
            }
            break;
        case 3:
            sync();
            printf("poweroff: halt issued to kernel\nSYSTEM IS GOING DOWN NOW!!\n");
            if (system("halt") == -1) {
                printf("poweroff: Failed to halt\n");
                return -1;
            }
            break;
        default:
            sync();
            printf("poweroff: no arguments, poweroff issued to kernel\nSYSTEM IS GOING DOWN NOW!!\n");
            if (system("shutdown") == -1) {
                printf("poweroff: Failed to poweroff\n");
                return -1;
            }
    }

    return 0;
}
