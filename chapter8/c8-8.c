//
// Created by 王琛超 on 2020/2/15.
//

//
// Created by 王琛超 on 2020/2/15.
//
#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

#define DELAY 5

void child_code(int);
void parent_code(int);

int main(int argc, char **argv) {
    int newpid;
    struct timeval it;
    gettimeofday(&it, NULL);
    assert(argc == 2);
    srand(it.tv_sec * 1000 + it.tv_usec / 1000);
    int thread_num = atoi(argv[1]);
    printf("before, my pid is %d\n", getpid());
    while ((newpid = fork()) != -1 && thread_num--) {
        if (newpid == 0) { // 子进程
            child_code(rand() % 10);
        } else {
            parent_code(newpid);
        }
    }
}
void child_code(int delay) {
    printf("child %d here, my parent is %d, will sleep for %d seconds\n",
           getpid(), getppid(), delay);
    sleep(delay);
    printf("child done. about to exit\n");
    exit(17);
}

void parent_code(int childpid) {
    int wait_rv;
    int child_status;
    int high_8, low_7, bit_7;

    wait_rv = wait(&child_status);
    printf("done waiting for %d. waiting returned: %d\n", childpid, wait_rv);

    high_8 = child_status >> 8;
    low_7 = child_status & 0x7F;
    bit_7 = child_status & 0x80;
    printf("status: exit=%d, sig=%d, core=%d\n", high_8, low_7, bit_7);
}

