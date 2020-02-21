//
// Created by 王琛超 on 2020/2/21.
//

// 客户端发送需要请求查看的目录

#include <stdio.h>
#include <assert.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <zconf.h>

#define oops(msg) {perror(msg); exit(1);}
#define PORTNUM 15000

int main(int argc, char **argv) {
    struct sockaddr_in servadd;
    int sock_id;
    char buffer[BUFSIZ];
    int n_read;

    assert(argc == 3);
    //1.
    if ((sock_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        oops("socket");
    }

    //2.
    memset(&servadd, 0, sizeof(servadd));
    servadd.sin_family = AF_INET;
    servadd.sin_addr.s_addr = inet_addr(argv[1]);
    printf("%s\n", argv[1]);
    servadd.sin_port = htons(PORTNUM);

    if (connect(sock_id, (struct sockaddr*)&servadd, sizeof(servadd)) != 0)
        oops("connect");

    //3.发送目录信息，然后从socket逐行读取返回的信息
    if (write(sock_id, argv[2], strlen(argv[2])) == -1)
        oops("write");
    if (write(sock_id,"\n",1) == -1)
        oops("write");
    while ((n_read = read(sock_id, buffer, BUFSIZ)) > 0) {
        if (write(1,buffer,n_read) == -1)
            oops("write");
    }
    close(sock_id);
}