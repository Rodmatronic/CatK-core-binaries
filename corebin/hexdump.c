// hexdump - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>

void hexdump(FILE *fp) {
    unsigned char buffer[16];
    size_t bytes_read;
    size_t offset = 0;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        printf("%08zx  ", offset);
        for (size_t i = 0; i < bytes_read; i++) {
            printf("%02x ", buffer[i]);
        }
        for (size_t i = bytes_read; i < sizeof(buffer); i++) {
            printf("   ");
        }
        printf(" ");
        for (size_t i = 0; i < bytes_read; i++) {
            if (buffer[i] >= 32 && buffer[i] <= 126) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }
        printf("\n");
        offset += bytes_read;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return -1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("hexdump: no such file or directory");
        return -1;
    }

    hexdump(fp);
    fclose(fp);

    return 0;
}
