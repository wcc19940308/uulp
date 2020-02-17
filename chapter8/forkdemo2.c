//
// Created by 王琛超 on 2020/2/15.
//

#include <stdio.h>
#include <zconf.h>

int main() {
    int ret_from_fork, mypid;
    mypid = getpid();
    printf("Before : my pid is %d\n", mypid);
    ret_from_fork = fork();

    sleep(1);
    printf("After: my pid is %d, fork() is %d\n", getpid(), ret_from_fork);

}

