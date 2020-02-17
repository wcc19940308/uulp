//
// Created by 王琛超 on 2020/2/10.
//

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv) {
    int fd;
    char buf[BUFSIZ];
    char *get_tty(), *tty_for_user;
    tty_for_user = get_tty(argv[1]);
    if (tty_for_user == NULL)
        return 1;
    printf("%s\n", tty_for_user);
    sprintf(buf, "/dev/%s", tty_for_user);
    printf("%s\n", buf);
    fd = open(buf, O_WRONLY);
    while (fgets(buf, BUFSIZ, stdin) != NULL) {
        if (write(fd, buf, strlen(buf)) == -1)
            break;
    }
    close(fd);
}

char *get_tty(char *logname) {
    static struct utmp utrec;
    int utfd;
    int namelen = sizeof(utrec.ut_user);
    char *retval = NULL;
    if ((utfd = open(UTMP_FILE, O_RDONLY)) == -1)
        return NULL;
    while (read(utfd, &utrec, sizeof(utrec)) == sizeof(utrec)) {
        if (strncmp(logname, utrec.ut_user, namelen) == 0) {
            retval = utrec.ut_line;
            break;
        }
    }
    close(utfd);
    return retval;
}

