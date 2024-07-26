// sh - core CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
#define SH_PROMPT "$ "

int motd() {
    FILE *file = fopen("/etc/motd", "r");
    if (file == NULL) {
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

void execute_command(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        printf("%s: command not found\n", args[0]);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        printf("Failed to fork process\n");
    } else {
        // Parent process
        waitpid(pid, &status, 0);
    }
}

void handle_redirection(char **args) {
    int fd;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            args[i] = NULL;
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (strcmp(args[i], ">>") == 0) {
            args[i] = NULL;
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (strcmp(args[i], "<") == 0) {
            args[i] = NULL;
            fd = open(args[i + 1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
    }
}

void handle_pipe(char **args) {
    int pipefd[2];
    pid_t pid;
    int status;

    char *cmd1[MAX_ARGS], *cmd2[MAX_ARGS];
    int i, j = 0, cmd1_done = 0;

    for (i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            args[i] = NULL;
            cmd1_done = 1;
            continue;
        }
        if (cmd1_done) {
            cmd2[j++] = args[i];
        } else {
            cmd1[i] = args[i];
        }
    }
    cmd2[j] = NULL;

    pipe(pipefd);
    pid = fork();
    if (pid == 0) {
        // Child process 1
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execvp(cmd1[0], cmd1);
        printf("%s: command not found\n", cmd1[0]);
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        printf("Failed to fork process\n");
    } else {
        // Parent process
        waitpid(pid, &status, 0);
        pid = fork();
        if (pid == 0) {
            // Child process 2
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            execvp(cmd2[0], cmd2);
            printf("%s: command not found\n", cmd2[0]);
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            printf("Failed to fork process\n");
        } else {
            // Parent process
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid, &status, 0);
        }
    }
}

int main() {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
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
                printf("cd: missing argument\n");
            } else if (chdir(args[1]) != 0) {
                printf("cd: %s: No such file or directory\n", args[1]);
            }
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            printf("exit\n");
            return -1;
        }

        // Check for pipes
        int has_pipe = 0;
        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], "|") == 0) {
                has_pipe = 1;
                break;
            }
        }

        if (has_pipe) {
            handle_pipe(args);
        } else {
            // Check for redirection
            int is_redirection = 0;
            for (int i = 0; args[i] != NULL; i++) {
                if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0 || strcmp(args[i], "<") == 0) {
                    is_redirection = 1;
                    break;
                }
            }

            if (is_redirection) {
                pid_t pid = fork();
                if (pid == 0) {
                    // Child process
                    handle_redirection(args);
                    execvp(args[0], args);
                    printf("%s: command not found\n", args[0]);
                    exit(EXIT_FAILURE);
                } else if (pid < 0) {
                    printf("Failed to fork process\n");
                } else {
                    // Parent process
                    waitpid(pid, NULL, 0);
                }
            } else {
                execute_command(args);
            }
        }
    }
    return 0;
}
