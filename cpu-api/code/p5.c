#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {
    int rc = fork();
    printf("pid: %d\n",  (int) getpid());
    if (rc == 0) {
        int rc_wait = wait(NULL);
        printf("pid: %d, rc_wait: %d\n",  (int) getpid(), rc_wait);
    } else {
        int rc_wait = wait(NULL);
        printf("pid: %d, rc_wait: %d\n",  (int) getpid(), rc_wait);
    }
    return 0;
}
