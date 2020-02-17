//
// Created by 王琛超 on 2020/2/15.
//

#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>

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
        parent_code(newpid);
    }
}

void child_code() {
    printf("child %d here. will sleep for %d seconds\n", getpid(), DELAY);
    sleep(DELAY);
    exit(100);
}

void parent_code(int childpid) {
    int wait_rv;
    wait_rv = wait(NULL);
    printf("done waiting for %d. Wait returned %d\n", childpid, wait_rv);
}

