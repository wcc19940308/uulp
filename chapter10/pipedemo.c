//
// Created by 王琛超 on 2020/2/20.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// apipe[0]是读端，apipe[1]是写入端。
// 数据流顺序:stdin -> buf -> apipe[1] -> apipe[0] / apipe[0] -> buf -> stdout
main() {
    int len, i, apipe[2];
    char buf[BUFSIZ];
    if (pipe(apipe) == -1) {
        perror("cannot pipe");
        exit(1);
    }
    printf("Got a pipe! It is file descriptors :{%d %d}\n",
           apipe[0], apipe[1]);
    while (fgets(buf, BUFSIZ, stdin)) {
        len = strlen(buf);
        if (write(apipe[1], buf, len) != len) {
            perror("write to pipe");
            break;
        }
        // 清空buf
        for (i = 0; i < len; i++) {
            buf[i] = 'X';
        }
        len = read(apipe[0], buf, BUFSIZ);
        if (write(1, buf, len) != len) {
            perror("write to 1");
            break;
        }
    }
    return 0;
}