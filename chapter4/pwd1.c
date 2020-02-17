//
// Created by 王琛超 on 2020/2/9.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <zconf.h>
#include <stdlib.h>
#include <string.h>

ino_t get_inode(char *);
void print_path_to(ino_t);
void inum_to_name(ino_t, char *, int);

int main() {
    print_path_to(get_inode("."));
    putchar('\n');
    return 0;
}

void print_path_to(ino_t this_inode) {
    ino_t my_inode;
    char its_name[BUFSIZ];
    if (get_inode("..") != this_inode) {
        // 用子目录的inode在父目录中找对应的文件名
        chdir("..");
        inum_to_name(this_inode, its_name, BUFSIZ);
        my_inode = get_inode(".");
        print_path_to(my_inode);
        // 每次结束只会输出当前目录下的那个名称
        printf("/%s", its_name);
    }
}

// 在父目录的当前目录下搜索相应inode的子文件名称
void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    if ((dir_ptr = opendir(".")) == NULL) {
        perror(".");
        exit(EXIT_FAILURE);
    }
    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        if (dirent_ptr->d_ino == inode_to_find) {
            // dest, scr, n(如果src长度小于n，则后面用空字符填充)
            strncpy(namebuf, dirent_ptr->d_name, buflen);
            namebuf[buflen - 1] = '\0';
            closedir(dir_ptr);
            return;
        }
    }
    fprintf(stderr, "error looking for inum %d\n", inode_to_find);
    exit(1);
}

ino_t get_inode(char *fname) {
    struct stat info;
    if (stat(fname, &info) == -1) {
        perror(fname);
        exit(EXIT_FAILURE);
    }
    return info.st_ino;
}




