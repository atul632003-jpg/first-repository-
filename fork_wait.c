#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int pid = fork();

    if (pid == 0) {
        execlp("ls", "ls", "-l", NULL);
    } else {
        printf("parent waiting...\n");

        int status;
        wait(&status);

        if (WIFEXITED(status))
            printf("child exited, code %d\n",
                   WEXITSTATUS(status));
    }

    return 0;
}

