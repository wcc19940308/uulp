//
// Created by 王琛超 on 2020/2/21.
//
#include  <stdio.h>
#include  <unistd.h>
#include  <sys/types.h>
#include  <sys/socket.h>
#include  <netinet/in.h>
#include  <netdb.h>
#include  <time.h>
#include  <strings.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORTNUM 15000
#define HOSTLEN 256
#define oops(msg) {perror(msg); exit(1);}

void sanitize(char *);
int main(int argc, char **argv) {
    struct sockaddr_in saddr;
    int sock_id, sock_fd; // 服务端自己绑定的socket以及连接过来的客户端socket
    FILE *sock_fpi, *sock_fpo; // 对客户端socket的读写文件指针
    FILE *pipe_fp;
    char dirname[BUFSIZ];
    char command[BUFSIZ];
    int c;

    if ((sock_id = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        oops("socket");
    }

    memset(&saddr, 0, sizeof(saddr));

    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;
    if (bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0)
        oops("bind");

    if (listen(sock_id, 1) != 0) {
        oops("listen");
    }

    while (1) {
        if ((sock_fd = accept(sock_id, NULL, NULL)) == -1) {
            oops("accept");
        }
        // 以文件的形式打开连接的客户端socket
        if ((sock_fpi = fdopen(sock_fd, "r")) == NULL) {
            oops("fdopen reading");
        }
        // 将目录的信息存到dirname中
        if (fgets(dirname, BUFSIZ - 5, sock_fpi) == NULL) {
            oops("reading dirname");
        }
        sanitize(dirname);

        if ((sock_fpo = fdopen(sock_fd,"w")) == NULL) {
            oops("fdopen writing");
        }
        sprintf(command, "ls %s",dirname);
        // 将执行好的结果放到pipe_fp文件中
        if ((pipe_fp = popen(command, "r")) == NULL) {
            oops("popen");
        }
        while ((c = getc(pipe_fp)) != EOF)
            putc(c, sock_fpo);
        pclose(pipe_fp);
        // 下面这个顺序不能改，改了客户端sock_fpo就无法显示数据了，感觉是缓冲区刷新的问题
        fclose(sock_fpo);
        fclose(sock_fpi);

    }
}

// 为了防止出现"ls; rm *"的情况,这个不是太懂
void sanitize(char *str) {
    char *src, *dest;
    for (src = dest = str; *src; src++) {
        if (*src == '/' || isalnum(*src)) {
            *src = *dest++;
        }
    }
    *dest = '\0';
}