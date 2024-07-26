#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char usename[128];
char password[128];

int printtime() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    // Get the current time
    time(&rawtime);

    // Convert to local time format
    timeinfo = localtime(&rawtime);

    // Format the time
    if (strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Z %Y", timeinfo) == 0) {
        printf("Error: strftime returned 0");
        exit(EXIT_FAILURE);
    }

    // Print the formatted time
    printf("%s\n\n", buffer);

    return 0;
}

int showunix() {
    FILE *file = fopen("/etc/issue", "r");
    if (file == NULL) {
        return 1;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\\') {
            c = fgetc(file);
            if (c == 'n') {
            } else if (c == 't') {
            } else if (c == 'l') {
                // Handle \l if needed, here we just ignore it.
                // You can add specific behavior if desired.
            } else if (c != EOF) {
            } else {
                putchar('\\');
            }
        } else {
            putchar(c);
        }
    }

    fclose(file);
    return 0;
}

int main() {
    printtime();
    showunix();
    while (1) {
        printf("Login: ");
        if (fgets(usename, sizeof(usename), stdin) == NULL) {
        }
        printf("Password: ");
        if (fgets(password, sizeof(password), stdin) == NULL) {
        }
        printf("Login incorrect\n");
    }
    return 0;
}
