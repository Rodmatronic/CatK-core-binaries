#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

// Function to disable echoing input characters
void disable_echo(struct termios *old, struct termios *new) {
    tcgetattr(fileno(stdin), old);
    *new = *old;
    new->c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), TCSAFLUSH, new);
}

// Function to restore the original terminal settings
void restore_echo(struct termios *old) {
    tcsetattr(fileno(stdin), TCSAFLUSH, old);
}

// Basic hashing function
unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

// Function to check if a user exists in /etc/passwd
int user_exists(const char *username) {
    FILE *fp = fopen("/etc/passwd", "r");
    if (!fp) {
        perror("fopen");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, username, strlen(username)) == 0 && line[strlen(username)] == ':') {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// Function to get and verify new password
void change_password(const char *username) {
    char password1[256], password2[256];
    struct termios oldt, newt;

    // Disable echo
    disable_echo(&oldt, &newt);

    printf("Enter new password: ");
    fgets(password1, sizeof(password1), stdin);
    password1[strcspn(password1, "\n")] = '\0';

    printf("\nConfirm new password: ");
    fgets(password2, sizeof(password2), stdin);
    password2[strcspn(password2, "\n")] = '\0';

    // Restore echo
    restore_echo(&oldt);

    if (strcmp(password1, password2) != 0) {
        fprintf(stderr, "\nPasswords do not match. Try again.\n");
        return;
    }

    unsigned long hashed_password = hash(password1);
    printf("\nPassword for user '%s' changed to hash: %lu\n", username, hashed_password);

    // Here you would write the hashed password to /etc/passwd or appropriate location
}

int main(int argc, char *argv[]) {
    char *username;

    if (argc == 2) {
        username = argv[1];
        if (!user_exists(username)) {
            fprintf(stderr, "User '%s' does not exist.\n", username);
            return 1;
        }
    } else {
        username = getenv("USER");
        if (!username || !user_exists(username)) {
            fprintf(stderr, "Current user does not exist or cannot be determined.\n");
            return 1;
        }
    }

    change_password(username);
    return 0;
}
