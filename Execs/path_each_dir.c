#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_path_directories() {
    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not found\n");
        return;
    }

    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    while (dir != NULL) {
        printf("%s\n", dir);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
}

