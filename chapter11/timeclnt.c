//
// Created by 王琛超 on 2020/2/21.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <zconf.h>

#define oops(msg) {perror(msg); exit(1);}

int main(int argc, char **argv) {
    struct sockaddr_in servadd;
    int sock_id, sock_fd;
    char message[BUFSIZ];
    int messlen;

    // 1.get a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id == -1)
    oops("socket");

    //2. connect to server
    memset(&servadd, 0, sizeof(servadd));
    servadd.sin_family = AF_INET;
    servadd.sin_addr.s_addr = inet_addr("127.0.0.1");
    servadd.sin_port = htons(13000);

    if (connect(sock_id, (struct sockaddr *)&servadd, sizeof(servadd)) != 0)
        oops("connect");

    // 3. transfer data from server, then hangup
    messlen = read(sock_id, message, BUFSIZ);
    if (messlen == -1) oops("read");
    // 把读到的数据输出到stdout上
    if (write(1,message,messlen) != messlen) oops("write");
    close(sock_id);
}
