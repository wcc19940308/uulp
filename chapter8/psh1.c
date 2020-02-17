//
// Created by 王琛超 on 2020/2/15.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXARGS 20
#define ARGLEN 100

char *makestring(char *);
void execute(char *[]);

int main() {
    char *arglist[MAXARGS + 1];
    int numargs;
    char argbuf[ARGLEN];


    numargs = 0;
    while (numargs < MAXARGS) {
        printf("Arg[%d]? ", numargs);
        // 只要读到的不是回车，就继续读
        if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n') {
            arglist[numargs++] = makestring(argbuf);
        } else {
            if (numargs > 0) {
                arglist[numargs] = NULL;
                execute(arglist);
                numargs = 0;
            }
        }
    }
    return 0;
}

void execute(char *arglist[]) {
    execvp(arglist[0], arglist);
    perror("execvp failed");
    exit(1);
}

char *makestring(char *argbuf) {
    char *cp;
    argbuf[strlen(argbuf) - 1] = '\0'; // 重置最后一个符号位
    cp = (char *) malloc(strlen(argbuf) + 1); // 因为strlen不算'\0'，所以要多申请1位
    if (cp == NULL) {
        perror("cannot allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(cp, argbuf);
    return cp;
}

