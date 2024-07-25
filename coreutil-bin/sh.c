
// sh - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
#define SH_PROMPT "$ "

int motd() {
    FILE *file = fopen("/etc/motd", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
    return 0;
}

void parse_command(char *cmd, char **args) {
    int i = 0;
    args[i] = strtok(cmd, " \t\n");
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " \t\n");
    }
}

int main() {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;
    motd();

    while (1) {
        printf("%s", SH_PROMPT);
        fflush(stdout);

        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            break;
        }

        parse_command(cmd, args);

        if (args[0] == NULL) {
            continue; // Empty command
        }

        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(args[1]) != 0) {
                perror("cd");
            }
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            printf("exit\n");
            exit(EXIT_SUCCESS);
        }

        pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            printf("%s: command not found\n", args[0]);
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}