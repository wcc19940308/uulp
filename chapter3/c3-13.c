//
// Created by 王琛超 on 2020/2/6.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

bool do_stat(char *name);

// 为了保证可以将文件复制到目录中
int main(int argc, char *argv[]) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    bool flag = false;
    char str[100];
    if (argc != 3) {
        perror("argc is error");
        exit(EXIT_FAILURE);
    }
    if ((in_fd = open(argv[1], O_RDONLY)) == -1) {
        perror("cannot open");
        exit(EXIT_FAILURE);
    }

    flag = do_stat(argv[2]);

    strcat(str, argv[2]);
    // 如果已经输入了/，那么就不需要再添加/了
    if (argv[2][strlen(argv[2]) - 1] != '/')
        strcat(str, "/");
    strcat(str, argv[1]);

    if ((out_fd = creat(str, COPYMODE)) != -1) {
        while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) {
            if ((write(out_fd, buf, n_chars)) != n_chars) {
                perror("write error");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (close(in_fd) == -1 || close(out_fd) == -1) {
        perror("cannot close ");
        exit(EXIT_FAILURE);
    }
    return 0;
}

bool do_stat(char *name) {
    struct stat stat_ptr;
    if (stat(name, &stat_ptr) == -1) {
        perror(name);
        exit(EXIT_FAILURE);
    }
    if (S_ISDIR(stat_ptr.st_mode)) {
        return true;
    }
    return false;
}