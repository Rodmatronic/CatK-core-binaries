
// uname - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

#define VERSION "1.0 CatK-uname"

int main(int argc, char *argv[]) {
    // Check if the number of arguments is greater than 10 (program name + 9 arguments)
    if (argc > 10) {
        printf("uname: usage: %s [-a | -v | -V | -m | -o | -s | -p | -n | -r ]\n", argv[0]);
        return -1;
    }

    struct utsname system_info;

    if (argc < 1) {
        if (uname(&system_info) == 0)
        {
            printf("%s\n", system_info.name);
            return 0;
        }
    } 

    int i;

    // Iterate through each argument
    for (i = 1; i < argc; i++) {

        // Util version
        if (strcmp(argv[i], "-V") == 0) {
            printf("uname: version: %s\n", VERSION);
            return 0;
        }

        // Full Kernel version
        if (strcmp(argv[i], "-a") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s %s %s %s %s %s %s %s %s ", system_info.name, system_info.host, system_info.release, system_info.version, system_info.machine, system_info.machine, system_info.processor, system_info.processor, system_info.os);
            }
        }

        // Kernel version
        if (strcmp(argv[i], "-s") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s ", system_info.name);
            }
        }

        // Kernel release version
        if (strcmp(argv[i], "-r") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s ", system_info.release);
            }
        }

        // Kernel version, full thing
        if (strcmp(argv[i], "-v") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s ", system_info.version);
            }
        }

        // Kernel CPU architecture
        if (strcmp(argv[i], "-m") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s ", system_info.machine);
            }
        }

        // Kernel arch target
        if (strcmp(argv[i], "-p") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s ", system_info.processor);
            }
        }

        // Kernel arch target (again)
        if (strcmp(argv[i], "-i") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s ", system_info.processor);
            }
        }

        // Kernel OS name (fancy)
        if (strcmp(argv[i], "-o") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s ", system_info.os);
            }
        }

        // The Nodename (hostname)
        if (strcmp(argv[i], "-n") == 0) {
            if (uname(&system_info) == 0)
            {
                printf("%s ", system_info.host);
            }
        }
    }
    printf("\n");
    return 0;
}