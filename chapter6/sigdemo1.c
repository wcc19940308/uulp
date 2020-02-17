//
// Created by 王琛超 on 2020/2/11.
//


#include <stdio.h>
#include <signal.h>
int main() {
    void f();
    signal(SIGINT, f);
    for (int i = 0; i < 5; i++) {
        printf("hello!\n");
        sleep(1);
    }
}

void f() {
    printf("signal is coming!\n");
}

