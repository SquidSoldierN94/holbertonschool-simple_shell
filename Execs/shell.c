#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

int main() {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    int status;

    while (1) {
        printf("simple_shell> ");
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\nExiting shell...\n");
            break;
        }

        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        // Exit command
        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execl(command, command, NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

