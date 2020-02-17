//
// Created by 王琛超 on 2020/2/4.
//

//
// Created by 王琛超 on 2020/2/4.
//


#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int fd1 = open("2.6.txt", O_RDONLY);
    int fd2 = open("2.6.txt", O_WRONLY);
    int fd3 = open("2.6.txt", O_RDONLY);

    char buf[21];
    buf[20] = '\0';

    if (read(fd1, buf, 20) == 20) {
        printf("%s\n", buf);
    }
    close(fd1);

    strcpy(buf, "testing 123...");
    int len = strlen(buf);
    if (write(fd2, buf, len) != len) {
        perror("2.6.txt");
        exit(EXIT_FAILURE);
    }
    close(fd2);

    if (read(fd3, buf, 20) == 20) {
        printf("%s\n", buf);
    }
    close(fd3);

    return EXIT_SUCCESS;
}

