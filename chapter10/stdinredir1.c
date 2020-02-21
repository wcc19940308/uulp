//
// Created by 王琛超 on 2020/2/20.
//

#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>

main() {
    int fd;
    char line[100];
    fgets(line, 100, stdin);
    printf("%s\n", line);
    fgets(line, 100, stdin);
    printf("%s\n", line);
    fgets(line, 100, stdin);
    printf("%s\n", line);

    close(0);
    if ((fd = open("/etc/passwd", O_RDONLY) == 0)) {
        fgets(line, 100, stdin);
        printf("%s\n", line);
        fgets(line, 100, stdin);
        printf("%s\n", line);
        fgets(line, 100, stdin);
        printf("%s\n", line);
    } else {
        fprintf(stderr, "cannot open fd 0\n");
    }
}
