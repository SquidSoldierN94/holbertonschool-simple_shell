#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int _unsetenv(const char *name) {
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        return -1;  // Invalid name
    }

    size_t name_len = strlen(name);
    int i, j;
    int found = 0;

    for (i = 0, j = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') {
            free(environ[i]);  // Free the memory of the removed variable
            found = 1;
        } else {
            environ[j] = environ[i];
            j++;
        }
    }

    if (found) {
        environ[j] = NULL;  // Ensure the array is NULL-terminated
    }

    return (found ? 0 : -1);  // Return 0 if variable was found and removed, -1 otherwise
}

