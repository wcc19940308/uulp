//
// Created by 王琛超 on 2020/2/15.
//
#include <stdio.h>
#include <zconf.h>

int main() {
    int n;
    for (n = 0; n < 10; n++) {
        printf("my pid = %d, n = %d\n", getpid(), n);
        sleep(1);
    }
}

