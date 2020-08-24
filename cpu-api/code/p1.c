#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {
    int x = 0;
    int rc = fork();
    printf("pid: %d, x: %d\n",  (int) getpid(), x);
    if (rc == 0) {
        x = 1;
        printf("pid: %d, x: %d\n",  (int) getpid(), x);
    } else {
        int rc_wait = wait(NULL);
        printf("pid: %d, x: %d\n",  (int) getpid(), x);
    }
    return 0;
}
