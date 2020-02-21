//
// Created by 王琛超 on 2020/2/21.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg) {perror(msg); exit(1);}

int main(int args, char **argv) {
    struct sockaddr_in saddr;
    struct hostent *hp;
    char hostname[HOSTLEN];
    int sock_id, sock_fd;
    FILE *sock_fp;
    char *ctime();
    time_t thetime;

    // 1.ask kernel for a socket
    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_id == -1)
        oops("socket");
    // 2.bind address to socket. Address is host, port
    bzero((void*)&saddr, sizeof(saddr));
    gethostname(hostname, HOSTLEN);
    hp = gethostbyname(hostname);

    // 下面这一步可能是unix中的地址的设定，现在已经没有了,但是可以用下面这样来代替
     //bcopy((void*)*(hp->h_addr_list), (void*)&saddr.sin_addr, hp->h_length);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if (bind(sock_id, (struct sockaddr *) &saddr, sizeof(saddr)) != 0) {
        oops("bind");
    }

    // 3.
    if (listen(sock_id, 1) != 0) {
        oops("listen");
    }

    while (1) {
        sock_fd = accept(sock_id, NULL, NULL);
        printf("Wow! get a call\n");
        if (sock_fd == -1)
            oops("accept");
        // 像操作文件一样操作连接进来的进程的socket
        sock_fp = fdopen(sock_fd, "w");
        if (sock_fp == NULL)
            oops("fdopen");
        thetime = time(NULL);
        fprintf(sock_fp, "The time here is..");
        fprintf(sock_fp, "%s", ctime(&thetime));
        fclose(sock_fp);
    }
}