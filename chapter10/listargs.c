//
// Created by 王琛超 on 2020/2/20.
//

#include <stdio.h>
main(int ac, char *av[]) {
    int i;
    printf("Number of args: %d, Args are:\n", ac);
    for (i = 0; i < ac; i++) {
        printf("args[%d] %s\n", i, av[i]);
    }
    fprintf(stderr, "This is sent to stderr\n");
}
