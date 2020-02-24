//
// Created by 王琛超 on 2020/2/24.
//

#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/un.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define	SOCKET	"/tmp/logfilesock"
#define	oops(m,x) { perror(m); exit(x); }

int main(int argc, char **argv) {
    int sock;
    struct sockaddr_un addr;
    socklen_t addrlen;
    char sockname[] = SOCKET;
    char *msg = argv[1];

    assert(argc == 2);
    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock == -1)
        oops("socket",2);
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, sockname);
    addrlen = strlen(sockname) + sizeof(addr.sun_family);
    if (sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&addr, addrlen) == -1)
        oops("sendto",3);

}