#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {
    int fd = open("./cpu-api/code/p2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int rc = fork();
    printf("pid: %d\n",  (int) getpid());
    if (rc == 0) {
        char buf[20] = "This is child\n";
        int sz = write(fd, buf, strlen(buf)); 
        printf("pid: %d, size: %d\n",  (int) getpid(), sz);
    } else {
        char buf[20] = "This is parent\n";
        int sz = write(fd, buf, strlen(buf)); 
        printf("pid: %d, size: %d\n",  (int) getpid(), sz);
    }
    close(fd);
    return 0;
}
