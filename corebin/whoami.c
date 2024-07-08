
// whoami - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    // Get the user ID of the calling process
    uid_t uid = getuid();
    
    // Get the password record for the user ID
    struct passwd *pw = getpwuid(uid);
    
    // Check if the password record is found
    if (pw) {
        // Print the username
        printf("%s\n", pw->pw_name);
    } else {
        // If no password record is found, print an error message
        printf("whoami: Failed to get username for UID %d\n", uid);
        return -1;
    }
    
    return 0;
}