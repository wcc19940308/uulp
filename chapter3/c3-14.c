//
// Created by 王琛超 on 2020/2/6.
//
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
void file_name_append(char *, char *, char*);
void file_copy(char *src, char *dest);


// 为了保证当两个参数都是目录的时候，可以整个文件夹下的文件全部复制到另一个文件夹下
int main(int argc, char *argv[]) {
    int in_fd;
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    struct stat stat_ptr;
    char *filename;
    bool flag1 = false, flag2 = false;
    if (argc != 3) {
        perror("argc is error");
        exit(EXIT_FAILURE);
    }
    // 检查是否是文件夹
    flag1 = do_stat(argv[1]);
    flag2 = do_stat(argv[2]);

    if (flag2) {
        // 如果都是文件夹，那么要对flag1进行遍历，然后对所有文件进行复制
        if (flag1) {
            if ((dir_ptr = opendir(argv[1])) == NULL) {
                perror("cannot opendir");
            }
            while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
                if (stat(filename = dirent_ptr->d_name, &stat_ptr) != -1) {
                    if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) break;
                    char str[100];
                    memset(str, '\0', strlen(str));
                    file_name_append(filename, argv[2], str);
                    file_copy(filename, str);
                }
            }
        } else {
            char str[100];
            memset(str, '\0', strlen(str));
            file_name_append(argv[1], argv[2], str);
            file_copy(argv[1], str);
        }
    }
    return 0;
}

void file_name_append(char *append, char name[], char *str) {
    strcat(str, name);
    int len = strlen(name) - 1;
    if (name[len] != '/')
        strcat(str, "/");
    strcat(str, append);
}

// 复制的是文件，可能src中依然含有目录，所以会有错误
void file_copy(char *src, char *dest) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];
    if ((in_fd = open(src, O_RDONLY)) == -1) {
        perror("cannot open");
        exit(EXIT_FAILURE);
    }
    if ((out_fd = creat(dest, COPYMODE)) == -1) {
        perror("cannot creat");
        exit(EXIT_FAILURE);
    }
    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) {
        if (write(out_fd, buf, n_chars) != n_chars) {
            perror("cannot write");
            exit(EXIT_FAILURE);
        }
    }

    if (close(in_fd) == -1 || close(out_fd) == -1) {
        perror("cannot close");
        exit(EXIT_FAILURE);
    }
}

// 是不是目录
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
