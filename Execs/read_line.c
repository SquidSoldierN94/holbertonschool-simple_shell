#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("$ ");
        fflush(stdout);

        read = getline(&line, &len, stdin);

        if (read == -1) {
            break;  // Exit on EOF (Ctrl+D)
        }

        // Remove newline character if present
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        printf("%s\n", line);

        // Exit if the user types "exit"
        if (strcmp(line, "exit") == 0) {
            break;
        }
    }

    free(line);  // Don't forget to free the allocated memory
    return 0;
}

