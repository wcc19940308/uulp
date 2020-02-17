//
// Created by 王琛超 on 2020/2/13.
//

#include <stdio.h>
#include <signal.h>
#define INPUTLEN 100

int main(int argc, char **argv) {
    void inthandler(int);
    void quithandler(int);
    char intput[INPUTLEN];
    int nchars;

    signal(SIGINT, inthandler);
    signal(SIGQUIT, quithandler);

    do {

        printf("\nType a message\n");
        nchars = read(0, intput, (INPUTLEN - 1));
        if (nchars == -1) perror("read return an error");
        else {
            intput[nchars] = '\0';
            printf("u typed: %s\n", __stdinp);
        }
    } while (strncmp(intput, "quit", 4) != 0);
}

void inthandler(int signum) {
    printf("Received signal %d .. waiting\n", signum);
    sleep(2);
    printf("Leaving inthandler\n");
}

void quithandler(int signum) {
    printf("Received signal %d .. waiting\n", signum);
    sleep(3);
    printf("Leaving quithandler\n");
}

