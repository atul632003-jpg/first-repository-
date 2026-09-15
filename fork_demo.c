#include <stdio.h>
#include <unistd.h>

int main(void) {
    int pid = fork();

    if (pid == 0)
        printf("child, pid=%d\n", getpid());
    else
        printf("parent, child pid=%d\n", pid);

    return 0;
}
