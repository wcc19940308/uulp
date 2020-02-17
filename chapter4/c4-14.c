//
// Created by 王琛超 on 2020/2/9.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MODE 0744

int main() {
    mkdir("demodlr", MODE);
    creat("y", MODE);
    chdir("demodlr");
    mkdir("a", MODE);
    mkdir("c", MODE);
    chdir("a");
    creat("x", MODE);
    chdir("../c");
    return EXIT_SUCCESS;
}

