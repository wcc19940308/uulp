//
// Created by 王琛超 on 2020/2/15.
//

#include <stdio.h>
#include <zconf.h>

int main() {
    printf("my pid is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("my pid is %d\n", getpid());
}

