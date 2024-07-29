
// whatis - CatK system binary
// Written by Rodmatronics

#include <stdio.h>
#include <string.h>

typedef struct {
    const char *command;
    const char *description;
} CommandInfo;

CommandInfo commands[] = {
    {"arch", "arch (1)             - print machine hardware name (same as uname -m)"},
    {"cat", "cat (1)              - concatenate files and print on the standard output"},
    {"clear", "clear (1)            - clear the terminal screen"},
    {"cp", "cp (1)               - copy files and directories"},
    {"echo", "echo (1)             - display a line of text"},
    {"grep", "grep (1)             - print lines that match patterns"},
    {"hexdump", "hexdump (1)          - display file contents in hexadecimal"},
    {"kill", "kill (1)             - send a signal to a process"},
    {"login", "login (1)            - begin session on the system"},
    {"ls", "ls (1)               - list directory contents"},
    {"mkdir", "mkdir (1)            - make directories"},
    {"more", "more (1)             - file perusal filter for crt viewing"},
    {"mv", "mv (1)               - move (rename) files"},
    {"rm", "rm (1)               - remove files or directories"},
    {"sh", "sh (1)               - command interpreter (shell)"},
    {"sleep", "sleep (1)            - delay for a specified amount of time"},
    {"uname", "uname (1)            - print system information"},
    {"usleep", "usleep (3)           - suspend execution for microsecond intervals"},
    {"which", "which (1)            - locate a command"},
    {"whoami", "whoami (1)           - print effective userid"},
    {"env", "env (1)              - print the current environment variables"},
    {"poweroff", "poweroff (8)         - Halt, power-off or reboot the machine"},
    {"setenv", "setenv (3)           - change or add an environment variable"},
    {"sync", "sync (1)             - Synchronize cached writes to persistent storage"},
    {"basename", "basename (1)         - strip directory and suffix from filenames"},
    {"realpath", "realpath (3)         - return the canonicalized absolute pathname"},
    {"rev", "rev (1)              - reverse lines characterwise"},
    {"whatis", "whatis (1)           - display one-line manual page descriptions"},
    {"yes", "yes (1)              - output a string repeatedly until killed"},
    //{"", ""},
};

const char* get_description(const char *command) {
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
        if (strcmp(commands[i].command, command) == 0) {
            return commands[i].description;
        }
    }
    return "whatis: nothing appropriate.";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <command>\n", argv[0]);
        return -1;
    }
    printf("%s\n", get_description(argv[1]));
    return 0;
}
