//
// Created by 王琛超 on 2020/2/4.
//

#include <dirent.h>
#include <stdio.h>

void do_ls(char[]);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        do_ls(".");
    } else {
        while (--argc) {
            // 先输出要ls的目录名称：
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }
    }
}

void do_ls(char name[]) {
    DIR *dir_ptr;
    struct dirent *direntp;
    // opendir相当于把目录中的所有文件都列举出来,包括.和..
    if ((dir_ptr = opendir(name)) == NULL) fprintf(stderr, "ls1: cannot open %s\n",name);
    else {
        while ((direntp = readdir(dir_ptr)) != NULL) {
            printf("%s\n", direntp->d_name);
        }
        closedir(dir_ptr);
    }
}