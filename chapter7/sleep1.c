//
// Created by 王琛超 on 2020/2/13.
//

#include <stdio.h>
#include <signal.h>

main() {
    void wakeup(int);

    printf("about to sleep for 4 sec\n");
    signal(SIGALRM, wakeup);
    alarm(4);
    pause();
    printf("Morning so soon?\n");
}

void wakeup(int signum) {
#ifndef SHHH
    printf("Alarm received");
#endif
}
