//
// Created by 王琛超 on 2020/2/10.
//
#include <stdio.h>

int main() {
    FILE *file1 = fopen("a", "a");
    FILE *file2 = fopen("a", "a");
    FILE *file3 = fopen("a", "w");

    fputs("123", file1);
    fflush(file1);

    fputs("abc", file2);
    fflush(file2);

    char buf[10];
    fscanf(file3, "%s", buf);
    printf("%s\n", buf);

    return 0;
}

