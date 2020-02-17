//
// Created by 王琛超 on 2020/2/9.
//

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>

int main(int argc, char **argv) {
    int fd;
    char buf[BUFSIZ];
    if (argc != 2) {
        perror(argc);
        exit(1);
    }
    if((fd = open(argv[1], O_WRONLY)) == -1) {
        perror("cannot open");
        exit(1);
    }
    while (fgets(buf, BUFSIZ, stdin) != NULL) {
        if (write(fd, buf, strlen(buf)) == -1) break;
    }
    close(fd);

}

