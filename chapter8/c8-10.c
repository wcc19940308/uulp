//
// Created by 王琛超 on 2020/2/16.
//

#include <assert.h>
#include <stdlib.h>
#include <zconf.h>
#include <stdio.h>
#include <signal.h>

void child_code(int);
void parent_code();

int thread_num = 0;
int count = 0;

int main(int argc, char **argv) {
    int pid;
    assert(argc == 2);
    thread_num = atoi(argv[1]);
    signal(SIGCHLD, parent_code);
    printf("before: my pid is %d\n", getpid());
    for (int i = 0; i < thread_num; i++) {
        child_code(5);
    }
    while (1) {
        printf("I am father in while\n");
        sleep(1);
    }
    return 0;
}

void child_code(int delay) {
    int pid;
    if ((pid = fork()) == -1) {
        perror("cannot fork");
    }
    // 子进程执行，父进程直接退出，继续循环
    if (pid == 0) {
        sleep(delay);
        printf("child exit, my father is %d\n", getpid());
        exit(100);
    }
}

void parent_code() {
    int wait_rv;
    int child_status;
    count++;
    while (wait_rv = waitpid(-1, &child_status, WNOHANG) > 0) {
        printf("wait number is %d\n", WEXITSTATUS(child_status));
    }
}
