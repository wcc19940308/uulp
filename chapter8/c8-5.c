//
// Created by 王琛超 on 2020/2/15.
//
//
#include <stdio.h>
#include <zconf.h>

main() {
    FILE *fp;
    int pid;
    char msg1[] = "Test 1,2,3\n";
    char msg2[] = "hello\n";

    if ((fp = fopen("testfile2", "w")) == NULL) {
        return 0;
    }
    fprintf(fp, "%s", msg1);
    if ((pid = fork()) == -1)
        return 0;
    if (pid != 0) {
        sleep(5);
    }
    fprintf(fp, "%s", msg2);
    fclose(fp);
    return 0;
}

