//
// Created by 王琛超 on 2020/2/7.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <string.h>

int main(int argc, char**argv) {
    char *filename = "c3-17.txt";
    char buf[1024];
    memset(buf, '\0',1024);
    int in_fd;
    if ((in_fd = open(filename, O_RDONLY)) == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    if (read(in_fd, buf, 2) != -1) {
        printf("%s\n", buf);
        sleep(20);
    }
    if (read(in_fd, buf, 2) != -1) {
        printf("%s\n", buf);
    }
    return 0;
}
