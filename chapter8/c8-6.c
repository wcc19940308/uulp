//
// Created by 王琛超 on 2020/2/15.
//

#include <stdlib.h>
#include <zconf.h>
#include <stdio.h>
main() {
    int i;
    if (fork() != 0) exit(0);
    for (int i = 0; i <= 10; i++) {
        printf("still here\n");
        sleep(i);
    }
    return 0;
}

