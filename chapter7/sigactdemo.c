//
// Created by 王琛超 on 2020/2/13.
//

#include <stdio.h>
#include <signal.h>
#define INPUTLEN 100

main() {
    struct sigaction newhandler;
    sigset_t blocked;
    void inthandler();
    char x[INPUTLEN];

    newhandler.sa_handler = inthandler;
    newhandler.sa_flags = SA_RESETHAND | SA_RESTART;

    // 初始化并设置
    sigemptyset(&blocked);
    sigaddset(&blocked, SIGQUIT);

    newhandler.sa_mask = blocked;

    // 设置SIGINT的新的handler，新的handler在处理SIGINT时阻塞SIGQUIT
    if (sigaction(SIGINT, &newhandler, NULL) == -1)
        perror("sigaction");
    else {
        while (1) {
            fgets(x, INPUTLEN, stdin);
            printf("input: %s", x);
        }
    }
}

void inthandler(int s) {
    printf("Called with signal %d\n", s);
    sleep(s);
    printf("done handling signal %d\n", s);
}

