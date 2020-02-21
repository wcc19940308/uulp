//
// Created by 王琛超 on 2020/2/20.
//

#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <stdlib.h>

#define CLOSE_DUP
//#define CLOSE_DUP2
main() {
    int fd, newfd;
    char line[100];
    fgets(line, 100, stdin);
    printf("%s\n", line);
    fgets(line, 100, stdin);
    printf("%s\n", line);
    fgets(line, 100, stdin);
    printf("%s\n", line);

    fd = open("/etc/passwd", O_RDONLY);

#ifdef CLOSE_DUP
    close(0);
    newfd = dup(fd);
#else
    newfd = dup2(fd,0);
#endif
    if (newfd != 0) {
        fprintf(stderr, "cannot dup()\n");
        exit(1);
    }
    close(fd);

    fgets(line, 100, stdin);
    printf("%s\n", line);
    fgets(line, 100, stdin);
    printf("%s\n", line);
    fgets(line, 100, stdin);
    printf("%s\n", line);
}

