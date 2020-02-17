//
// Created by 王琛超 on 2020/2/13.
//

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

int main() {
    void countdown(int);
    int set_ticker(int);
    signal(SIGALRM, countdown);
    // 设置并启动计时器
    if (set_ticker(500) == -1) {
        perror("set ticker");
    } else {
        while (1) pause();
    }
    return 0;
}

void countdown(int signum) {
    static int num = 10;
    printf("%d ..", num--);
    fflush(stdout);
    if (num < 0) {
        printf("DONE\n");
        exit(0);
    }
}

int set_ticker(int n_msecs) {
    struct itimerval new_timeset;
    long n_sec, n_usecs;

    n_sec = n_msecs / 1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;

    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

