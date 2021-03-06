//
// Created by 王琛超 on 2020/2/24.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <zconf.h>
#include "dgram.h"

#define SERVER_PORTNUM	2020		/* Our server's port number */
#define MSGLEN		128		/* Size of our datagrams */
#define TICKET_AVAIL	0		/* Slot is available for use */
#define MAXUSERS	3		/* Only 3 users for us */
#define	oops(x)	{ perror(x); exit(-1); }

#define RECLAIM_INTERVAL 5

int ticket_array[MAXUSERS];
int sd = -1;
int num_ticket_out = 0;
char *do_hello(char *);
char *do_goodbye(char *);
void free_all_tickets();
void narrate(char *, char *, struct sockaddr_in*);
int setup() {
    sd = make_dgram_server_socket(SERVER_PORTNUM);
    if (sd == -1)
        oops("make socket");
    free_all_tickets();
    return sd;
}

void free_all_tickets() {
    for (int i = 0; i < MAXUSERS; i++) {
        ticket_array[i] = TICKET_AVAIL;
    }
}

void shut_down() {
    close(sd);
}

void handle_request(char *req, struct sockaddr_in *client, socklen_t addlen) {
    char *response;
    int ret;
    if (strncmp(req,"HELO",4) == 0)
        response = do_hello(req);
    else if (strncmp(req, "GBYE", 4) == 0)
        response = do_goodbye(req);
    // 对客户端的检查
    else if (strncmp(req, "VALD",4) == 0)
        response = do_validate(req);
    else
        response = "FALL invalid request";
    narrate("SAID:", response, client);
    ret = sendto(sd,response,strlen(response),0,(struct sockaddr*)client, addlen);
    if (ret == -1)
        perror("SERVER sendto failed");
}

char *do_hello(char *msg_p) {
    int x;
    static char replybuf[MSGLEN];
    if (num_ticket_out >= MAXUSERS) {
        return "FAIL no tickets available";
    }
    for (x = 0; x < MAXUSERS && ticket_array[x] != TICKET_AVAIL; x++);
    if (x == MAXUSERS) {
        narrate("database corrput", "", NULL);
        return "FAIL database corrput";
    }
    ticket_array[x] = atoi(msg_p + 5); // 字符串转换成整数（ascii to integer）
    sprintf(replybuf,"TICK %d.%d",ticket_array[x],x);
    num_ticket_out++;
    return replybuf;
}

char *do_goodbye(char *msg_p) {
    int pid, slot;
    if ((sscanf((msg_p + 5), "%d.%d", &pid, &slot) != 2) || (ticket_array[slot] != pid)) {
        narrate("Bogus ticket", msg_p + 5, NULL);
        return "FAIL invalid ticket";
    }
    ticket_array[slot] = TICKET_AVAIL;
    num_ticket_out--;
    return "THNX See ya!";
}

void narrate(char *msg1, char *msg2, struct sockaddr_in *clientp)
{
    fprintf(stderr,"\t\tSERVER: %s %s ", msg1, msg2);
    if ( clientp )
        fprintf(stderr,"(%s:%d)", inet_ntoa(clientp->sin_addr),
                ntohs(clientp->sin_port) );
    putc('\n', stderr);
}

char *do_validate(char *msg) {
    int pid, slot;
    if ((sscanf((msg + 5), "%d.%d", &pid, &slot) == 2 && ticket_array[slot] == pid)) {
        return "GOOD Valid ticket";
    }
    narrate("Bogus ticket", msg + 5, NULL);
    return "FAIL invalid ticket";
}

void ticket_reclaim() {
    int i;
    char tick[BUFSIZ];
    for (i = 0; i < MAXUSERS; i++) {
        if ((ticket_array[i] != TICKET_AVAIL) &&
            (kill(ticket_array[i], 0) == -1) && (errno == ESRCH)) {
            sprintf(tick, "%d.%d", ticket_array[i], i);
            narrate("freeing", tick, NULL);
            ticket_array[i] = TICKET_AVAIL;
            num_ticket_out--;
        }
    }
    alarm(RECLAIM_INTERVAL);
}
