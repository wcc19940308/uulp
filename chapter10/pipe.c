//
// Created by 王琛超 on 2020/2/20.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#define oops(m, x) {perror(m); exit(x);}

int main(int argc, char **argv) {
    int fdpipe[2];
    int pid;
    assert(argc == 3);
    if (pipe(fdpipe) == -1) {
        oops("pipe",1);
    }
    if ((pid = fork()) == -1) {
        oops("fork",1);
    }
    if (pid > 0) {
        // close(fdpipe[1]);
        if (dup2(fdpipe[0], 0) == -1){
            perror("dup2");
        }
        close(fdpipe[0]);
        execlp(argv[2], argv[2], NULL);
    } else {
        close(fdpipe[0]);
        if (dup2(fdpipe[1], 1) == -1) {
            perror("dup2");
        }
        close(fdpipe[1]);
        execlp(argv[1], argv[1], NULL);
    }
}