#include <zconf.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

//
// Created by 王琛超 on 2020/2/9.
//
void print_path(ino_t);
ino_t get_inode(char *);
void inode_to_name(ino_t, char*, int);

int main() {
    print_path(get_inode("."));
    putchar('\n');

    return 0;
}

void print_path(ino_t this_node) {
    ino_t my_node;
    char buf[BUFSIZ];
    if (get_inode("..") != this_node) {
        chdir("..");
        inode_to_name(this_node, buf, BUFSIZ);
        print_path(get_inode("."));
        printf("/%s", buf);
    }
}

void inode_to_name(ino_t inode_to_find, char *str, int buflen) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    if ((dir_ptr = opendir(".")) != NULL) {
        while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
            if (dirent_ptr->d_ino == inode_to_find) {
                strncpy(str, dirent_ptr->d_name, BUFSIZ);
                str[BUFSIZ - 1] = '\0';
                closedir(dir_ptr);
                return;
            }
        }
    }
    perror(inode_to_find);
    exit(-1);
}


ino_t get_inode(char *filename) {
    struct stat stat_ptr;
    if ((stat(filename, &stat_ptr)) == -1) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    return stat_ptr.st_ino;
}

