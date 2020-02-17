//
// Created by 王琛超 on 2020/2/15.
//

#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <signal.h>


#define DELAY 2
void child_code();
void parent_code(int childpid);

int main() {
    int newpid;
    printf("before: my pid id %d\n", getpid());
    if ((newpid = fork()) == -1) {
        perror("cannot fork()");
    } else if (newpid == 0) {
        child_code();
    } else {
        signal(SIGCHLD, parent_code);
        while (1) {
            printf("wating\n");
            sleep(1);
        }
    }
}

void child_code() {
    printf("child %d here. will sleep for %d seconds\n", getpid(), DELAY);
    sleep(DELAY);
    exit(100);
}

void parent_code(int childpid) {
    int child_status;
    int wait_rv = wait(&child_status);

    printf("done waiting for %d, wait returned %d\n", childpid, wait_rv);

    int high_8 = child_status >> 8;
    int low_7 = child_status & 0x7F;
    int bit_7 = child_status & 0x80;
    printf("high_8: %d, low_7: %d, bit_7: %d\n", high_8, low_7, bit_7);
    exit(EXIT_SUCCESS);
}

