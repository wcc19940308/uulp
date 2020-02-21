//
// Created by 王琛超 on 2020/2/20.
//

#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <fcntl.h>

main() {
    int pid;
    int fd;
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        close(1);
        fd = creat("userlist", 0644);
        execlp("who", "who", NULL);
        perror("execlp");
        exit(1);
    }
    if (pid != 0) {
        wait(NULL);
        printf("done running\n");
    }
}
