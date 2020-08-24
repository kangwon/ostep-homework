#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MSGSIZE 20

int main(int argc, const char * argv[]) {
    int p[2];
    if (pipe(p) < 0) {
        printf (stderr, "Pipe failed.\n");
        exit(1); 
    }
  
    int c1_pid, c2_pid;
    (c1_pid = fork()) && (c2_pid = fork());
    printf("pid: %d\n",  (int) getpid());
    if (c1_pid == 0) {
        char msg[MSGSIZE] = "hello world";
        write(p[1], msg, MSGSIZE);
        printf("Send message: %s\n", msg);
    } else if (c2_pid == 0) {
        char inbuf[MSGSIZE];
        read(p[0], inbuf, MSGSIZE); 
        printf("Received message: %s\n", inbuf); 
    } else {
        int rc_wait = wait(NULL);
        printf("Parent finished\n");
    }
    return 0;
}
