//
// Created by 王琛超 on 2020/2/10.
//

#include <utmp.h>
#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include <stdlib.h>

char *get_tty(char *);
int main(int argc, char **argv) {
    int fd;
    char buf[BUFSIZ];
    if (argc != 2) {
        perror(argc);
        exit(EXIT_FAILURE);
    }
    char *tty_name = get_tty(argv[1]);
    if (tty_name == NULL) {
        printf(" cannot find %s\n", argv[1]);
        return 1;
    }
    sprintf(buf,"/dev/%s",tty_name);
    printf("Welcome, u are chatting with %s now\n", tty_name);

    if((fd = open(buf, O_WRONLY)) != -1) {
        // 这里相当于把buf复用了一下
        while (fgets(buf, BUFSIZ, stdin) != NULL) {
            if (write(fd, buf,BUFSIZ) == -1) break;
        }
    }
    close(fd);
}

char *get_tty(char *logname) {
    struct utmp utmprecv;
    int utfd;
    char *retval;
    if ((utfd = open(UTMP_FILE, O_RDONLY)) != -1) {
        while (read(utfd, &utmprecv, sizeof(utmprecv)) == sizeof(utmprecv)) {
            if (strncmp(logname, utmprecv.ut_user, strlen(utmprecv.ut_user)) == 0) {
                retval = utmprecv.ut_line;
                break;
            }
        }
    }
    close(utfd);
    return retval;
}

