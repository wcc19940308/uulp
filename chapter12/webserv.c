//
// Created by 王琛超 on 2020/2/22.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <zconf.h>
#include <stdbool.h>

int make_server_socket(int);
void read_til_crnl(FILE*);
void process_rq(char *, int);
void cannot_do(int);
void do_404(char *, int);
bool not_exist(char *);
bool isadir(char *);
void do_ls(char *, int);
char *file_type(char *);
bool ends_in_cgi(char *);
void do_exec(char *, int fd);
void do_cat(char *, int);


// 仅支持get请求的http服务器,支持ls，执行cgi，以及cat
int main(int argc, char **argv) {
    int sock, fd;
    FILE *fpin;
    char request[BUFSIZ];
    assert(argc != 1);
    // 绑定socket，并且listen
    sock = make_server_socket(atoi(argv[1]));
    if (sock == -1) exit(2);
    while (1) {
        fd = accept(sock, NULL, NULL);

        // 先读fd，获得请求
        fpin = fdopen(fd, "r");
        fgets(request, BUFSIZ, fpin);
        printf("got a call: request = %s", request);
        read_til_crnl(fpin);

        // 再写fd，写入响应
        process_rq(request, fd);
        fclose(fpin);
    }
}

void read_til_crnl(FILE *fp) {
    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, fp) != NULL && strcmp(buf, "\r\n") != 0);
}

// 每次启动一个子进程处理请求客户端的fd
void process_rq(char *rq, int fd) {
    char cmd[BUFSIZ], arg[BUFSIZ];
    // 这里是子进程的流程，因此调试的时候需要切换到子进程
    if (fork() != 0)
        return;
    strcpy(arg, "./");
    printf("before: %s\n", arg);
    // 这里是为了拼接查找的目录，arg原先为"./"，arg+2相当于在./目录下查找相应的文件
    if (sscanf(rq, "%s%s", cmd, arg + 2) != 2)
        return;
    // 必须是GET请求
    printf("after: %s\n", arg);
    if(strcmp(cmd, "GET") != 0)
        cannot_do(fd);
    else if (not_exist(arg))
        do_404(arg, fd);
    else if (isadir(arg))
        do_ls(arg, fd);
    else if (ends_in_cgi(arg))
        do_exec(arg, fd);
    else
        do_cat(arg, fd);
}

// 设置响应头
void header(FILE *fp, char *content_type) {
    fprintf(fp, "HTTP/1.1 200 OK\r\n");
    if (content_type)
        fprintf(fp, "Content-type: %s\r\n", content_type );
}

// http返回服务器501,
void cannot_do(int fd) {
    FILE *fp = fdopen(fd, "w");
    fprintf(fp, "HTTP/1.1 501 Not Implemented\r\n");
    fprintf(fp, "Content-type: textp/plain\r\n");
    fprintf(fp, "\r\n");

    fprintf(fp, "That command is not yet implemented\r\n");
    fclose(fp);
}

// http返回404错误，都是往fd里面写，大同小异
void do_404(char *item, int fd) {
    FILE *fp = fdopen(fd, "w");
    fprintf(fp, "Content-type: text/plain\r\n");
    fprintf(fp, "\r\n");

    fprintf(fp, "The item you requested: %s\r\nis not found\r\n",
            item);
    fclose(fp);
}

bool isadir(char *f) {
    struct stat info;
    return (stat(f, &info) != -1 && S_ISDIR(info.st_mode));
}

bool not_exist(char *f) {
    struct stat info;
    return (stat(f, &info) == -1);
}

void do_ls(char *dir, int fd) {
    FILE *fp;
    fp = fdopen(fd, "w");
    header(fp, "text/plain");
    fprintf(fp, "\r\n");
    fflush(fp);

    // 把ls的输出重定向到fd
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    execlp("ls", "ls", "-l", dir, NULL);
    perror(dir);
    exit(1);
}

char *file_type(char *f) {
    char *cp;
    if ((cp = strchr(f, '.')) != NULL) {
        return cp + 1;
    }
    return "";
}

bool ends_in_cgi(char *f) {
    return (strcmp(file_type(f), "cgi") == 0);
}

void do_exec(char *prog, int fd) {
    FILE *fp;
    fp = fdopen(fd, "w");
    header(fp, NULL);
    fflush(fp);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    execl(prog, prog, NULL);
    perror(prog);
}

void do_cat(char *f, int fd) {
    char *extension = file_type(f);
    char *content = "text/plain";
    FILE *fpsock, *fpfile;
    int c;

    if (strcmp(extension, "html") == 0)
        content = "text/html";
    else if (strcmp(extension,"gif") == 0)
        content = "image/gif";
    else if (strcmp(extension, "jpg") == 0)
        content = "image/jpg";
    else if (strcmp(extension, "jpeg") == 0)
        content = "image/jpeg";

    fpsock = fdopen(fd, "w");
    fpfile = fopen(f, "r");
    if (fpsock != NULL && fpfile != NULL) {
        header(fpsock, content);
        fprintf(fpsock, "\r\n");
        while ((c = getc(fpfile)) != EOF) {
            putc(c, fpsock);
        }
        fclose(fpfile);
        fclose(fpsock);
    }
    exit(0);
}
