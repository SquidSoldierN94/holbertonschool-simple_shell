#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[], char *env[]) {
    printf("Address of env (3rd parameter of main): %p\n", (void *)env);
    printf("Address of environ (global variable): %p\n", (void *)environ);

    if (env == environ) {
        printf("env and environ point to the same address\n");
    } else {
        printf("env and environ point to different addresses\n");
    }

    return 0;
}

