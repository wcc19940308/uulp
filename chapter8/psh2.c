//
// Created by 王琛超 on 2020/2/15.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


#define MAXARGS 20
#define ARGLEN 100

char *makestring(char *);
void execute(char *[]);

int main() {
    char *arglist[MAXARGS + 1];
    int numargs;
    char buf[ARGLEN];

    numargs = 0;
    while (numargs < MAXARGS) {
        printf("Args[%d]? ", numargs);
        if ((fgets(buf, ARGLEN, stdin)) && *buf != '\n') {
            arglist[numargs++] = makestring(buf);
        } else {
            if (numargs > 0) {
                arglist[numargs] = NULL;
                execute(arglist);
                while (--numargs >= 0)
                    free(arglist[numargs]);
                numargs = 0;
            }
        }
    }
    return 0;
}

char *makestring(char *buf) {
    char *c;
    buf[strlen(buf) - 1] = '\0';
    c = (char*) malloc(strlen(buf) + 1);
    strcpy(c, buf);
    return c;
}

void execute(char *arglist[]) {
    int pid, exitstatus;
    pid = fork();
    switch (pid) {
        case -1:
            perror("cannot fork");
            exit(1);
        case 0:
            execvp(arglist[0], arglist);
            perror("execvp failed");
            exit(1);
        default: {
            while (wait(&exitstatus) != pid);
            printf("child exited with status %d, %d\n", exitstatus >> 8, exitstatus & 0377);
        }
    }
}