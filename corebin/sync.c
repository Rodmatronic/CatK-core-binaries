
// sync - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Call the sync system call to flush filesystem buffers
    sync();
    return 0;
}
