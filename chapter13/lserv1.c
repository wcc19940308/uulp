//
// Created by 王琛超 on 2020/2/24.
//


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/errno.h>
#include <zconf.h>

#define MSGLEN		128		/* Size of our datagrams */
#define RECLAIM_INTERVAL 5

int setup();
void narrate(char *, char*, struct sockaddr_in*);
void handle_request(char *, struct sockaddr_in*, socklen_t);
void ticket_reclaim();
int main(int argc, char **argv) {
    struct sockaddr_in client_addr;
    socklen_t addrlen;
    char buf[MSGLEN];
    int ret;
    int sock;
    unsigned time_left;

    sock = setup();
    // 通过服务端周期检查客户端的进程是否存在，以检测客户端崩溃的情况
    signal(SIGALRM, ticket_reclaim);
    alarm(RECLAIM_INTERVAL);

    while (1) {
        addrlen = sizeof(client_addr);
        ret = recvfrom(sock, buf, MSGLEN, 0, (struct sockaddr*)&client_addr, &addrlen);
        if (ret != -1) {
            buf[ret] = '\0';
            narrate("GOT:", buf, &client_addr);
            time_left = alarm(0);
            handle_request(buf, &client_addr, addrlen);
            alarm(time_left);
        } else if (errno != EINTR) {
            perror("recvfrom");
        }
    }
}

