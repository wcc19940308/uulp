//
// Created by 王琛超 on 2020/2/4.
//
//

#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    struct stat my_stat;
    if (stat("/etc/passwd", &my_stat) == -1) {
        perror("/etc/passwd");
    } else {
        printf("The size of /etc/passwd is %d\n", my_stat.st_size);
    }

}

