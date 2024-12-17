#include <string.h>

extern char **environ;

char *_getenv(const char *name) {
    if (name == NULL || environ == NULL) {
        return NULL;
    }

    size_t name_len = strlen(name);

    for (char **env = environ; *env != NULL; env++) {
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=') {
            return &((*env)[name_len + 1]);
        }
    }

    return NULL;
}

