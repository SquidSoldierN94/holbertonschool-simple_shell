#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define MAX_PATH_LENGTH 4096
#define MAX_FILENAME_LENGTH 256

void search_file(const char *filename) {
    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not found\n");
        return;
    }

    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    while (dir != NULL) {
        char full_path[MAX_PATH_LENGTH];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, filename);

        if (access(full_path, X_OK) == 0) {
            printf("%s\n", full_path);
            free(path_copy);
            return;
        }

        dir = strtok(NULL, ":");
    }

    fprintf(stderr, "%s: not found in PATH\n", filename);
    free(path_copy);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        search_file(argv[i]);
    }

    return 0;
}

