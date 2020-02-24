/***************************************************************
 *	dgram.c
 *	support functions for datagram based programs
 */

#include	<stdio.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<string.h>

#define   HOSTLEN  256

int make_internet_address(char *, int, struct sockaddr_in *);

int make_dgram_server_socket(int portnum)
{
    struct  sockaddr_in   saddr;   /* build our address here */
    int	sock_id;	       /* the socket             */
    char host[BUFSIZ];
    sock_id = socket(PF_INET, SOCK_DGRAM, 0);  /* get a socket */
    if ( sock_id == -1 ) return -1;

    /** build address and bind it to socket **/

    /* where am I ?         */
    make_internet_address(host, portnum, &saddr);

    if ( bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0 )
        return -1;

    return sock_id;
}
int make_dgram_client_socket()
{
    return socket(PF_INET, SOCK_DGRAM, 0);
}

int make_internet_address(char * host,int port, struct sockaddr_in *addrp)
/*
 * constructor for an Internet socket address, uses hostname and port
 *   (host,port) -> *addrp
 */
{
    memset((void *) addrp, 0, sizeof(*addrp));
    addrp->sin_addr.s_addr = htonl(INADDR_ANY);
    addrp->sin_port = htons(port);
    addrp->sin_family = AF_INET;
    return 0;
}

// 将网络序转换，获得地址和端口
int get_internet_address(char *host, int len, int *portp, struct sockaddr_in *addrp)
/*
 * extracts host and port from an internet socket address
 *   *addrp -> (host,port)
 */
{

    strncpy(host, inet_ntoa(addrp->sin_addr), len );
    *portp = ntohs(addrp->sin_port);
    return 0;
}