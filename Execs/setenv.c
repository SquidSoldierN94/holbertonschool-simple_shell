#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int _setenv(const char *name, const char *value, int overwrite) {
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        return -1;  // Invalid name
    }

    size_t len = strlen(name) + strlen(value) + 2;  // +2 for '=' and null terminator
    char *new_var = malloc(len);
    if (new_var == NULL) {
        return -1;  // Memory allocation failed
    }

    snprintf(new_var, len, "%s=%s", name, value);

    int i;
    for (i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=') {
            if (!overwrite) {
                free(new_var);
                return 0;  // Variable exists and overwrite is not allowed
            }
            free(environ[i]);
            environ[i] = new_var;
            return 0;  // Successfully updated
        }
    }

    // Variable not found, add it
    char **new_environ = realloc(environ, (i + 2) * sizeof(char *));
    if (new_environ == NULL) {
        free(new_var);
        return -1;  // Memory allocation failed
    }

    environ = new_environ;
    environ[i] = new_var;
    environ[i + 1] = NULL;

    return 0;  // Successfully added
}

