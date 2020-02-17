//
// Created by 王琛超 on 2020/2/4.
//

#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char buf[100];
    int fd1 = open("2.9.txt", O_RDONLY);
    lseek(fd1, 100, SEEK_END);
    if (read(fd1, buf, 100) == 100) {
        printf("read succes from lseek 100 and no error\n");
    } else {
        perror("read error from lseek 100\n");
    }
    close(fd1);

    int fd2 = open("2.9.txt", O_WRONLY);
    lseek(fd2, 100, SEEK_END);
    if (write(fd2, "hello", 5) == 5) {
        printf("write succes to lseek 100 and no error\n");
    } else {
        perror("write error to lseek 100\n");
    }
    close(fd2);

    int fd3 = open("2.9.txt", O_WRONLY);
    lseek(fd3, 20000, SEEK_END);
    if (write(fd3, "hello", 5) == 5) {
        printf("write succes to lseek 20000 and no error\n");
    } else {
        perror("write error to lseek 20000\n");
    }
    close(fd3);
    return 0;
}

