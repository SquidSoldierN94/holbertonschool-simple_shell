#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    
    for (int i = 0; i < 5; i++) {
        pid = fork();
        
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("Child %d (PID: %d) executing ls -l /tmp\n", i + 1, getpid());
            execl("/bin/ls", "ls", "-l", "/tmp", NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(pid, &status, 0);
            printf("Child %d (PID: %d) has finished execution\n", i + 1, pid);
        }
    }
    
    printf("All child processes have completed\n");
    return 0;
}

