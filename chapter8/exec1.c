//
// Created by 王琛超 on 2020/2/15.
//

#include <stdio.h>
#include <zconf.h>

main() {
    char *arglist[3];

    arglist[0] = "ls";
    arglist[1] = "-l";
    arglist[2] = 0;

    printf("Already to exec ls -l\n");
    execvp("ls", arglist);
    printf("over\n");

}
