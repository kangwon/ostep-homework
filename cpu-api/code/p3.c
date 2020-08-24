#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

short flag = 0;

void handler(int signum) {
    flag = 1;
}

int main(int argc, const char * argv[]) {
    int rc = fork();
    if (rc == 0) {
        printf("pid: %d, this is child\n",  (int) getpid());
        kill(getppid(), SIGUSR1);
    } else {
        signal(SIGUSR1, handler);
        while (flag == 0) {}
        printf("pid: %d, this is parent\n",  (int) getpid());
    }
    return 0;
}
