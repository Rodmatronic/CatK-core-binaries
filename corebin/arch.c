
// arch - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

#define VERSION "1.0 CatK-arch"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        printf("arch: usage: %s [-V]\n", argv[0]);
        return -1;
    }

    if (strcmp(argv[1], "-V") == 0) {
        printf("arch: version: %s\n", VERSION);
        return 0;
    } else {
        struct utsname system_info;

        if (uname(&system_info) == 0)
        {
            printf("%s\n", system_info.machine);
        } else {
            printf("Failed to get ARCH from utsname\n");
            return -1;
        }
    }

    return 0;
}
