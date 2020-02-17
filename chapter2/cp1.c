//
// Created by 王琛超 on 2020/1/31.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include <stdbool.h>


#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);

int main(int argc, char *argv[]) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];

    if (argc < 3) {
        perror("bad source destination");
        exit(1);
    }
    bool prompt_mode = false;
    if (argc == 4) {
        int i = 1;
        while (i < argc) {
            if (strcmp(argv[i], "-i") == 0) {
                prompt_mode = true;
                break;
            }
            i++;
        }
    }

    if (prompt_mode) {
        printf("Do u want to replace %s by %s?\n", argv[2], argv[1]);
        char response[10];
        scanf("%s", response);
        if (strcmp(response, "n") == 0 || strcmp(response, "no") == 0) {
            exit(EXIT_SUCCESS);
        }
    }

    if ((in_fd = open(argv[1], O_RDONLY)) == -1) {
        oops("Cannot open", argv[1]);
    }
    if ((out_fd = creat(argv[2], COPYMODE)) == -1) {
        oops("Cannot creat", argv[2]);
    }
    if (argv[1] == argv[2]) {
        printf("you cannot do this");
        exit(1);
    }

    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) {
        if (write(out_fd, buf, n_chars) != n_chars) {
            oops("Write error to", argv[2]);
        }
    }
    if (n_chars == -1) {
        oops("Read error to", argv[1]);
    }
    if (close(in_fd) == -1 || close(out_fd) == -1) {
        oops("Error closing files", "");
    }

}

void oops(char *src, char *dest) {
    // 这里相当于拼接了stderr的内容，fprintf+ferror的内容
    fprintf(stderr, "Error: %s ", src);
    perror(dest);
    exit(1);
}
