//
// Created by 王琛超 on 2020/2/1.
//

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>
#include <unistd.h>

#define NRECS 16
#define NULLUT ((struct utmp*)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp = -1;

int utmp_open(char *filename) {
    fd_utmp = open(filename, O_RDONLY);
    cur_rec = num_recs = 0;
    return fd_utmp;
}

int umpt_reload() {
    int amt_read;
    // 执行read系统调用将文件中下一块长度为NRECS*UTSIZE的数据读取到缓冲区中
    amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
    // 读了多少个utmp
    num_recs = amt_read / UTSIZE;
    // 每次再从缓冲区中的第一块开始读取
    cur_rec = 0;
    return num_recs;
}

// 读取这个缓冲区中的下一个utmp，每读1个递增一次
struct utmp *utmp_next() {
    struct utmp *recp;
    if (fd_utmp == -1) return NULLUT;
    if (cur_rec == num_recs && umpt_reload() == 0) return NULLUT;
    recp = (struct utmp*)utmpbuf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}

void utmp_close() {
    if (fd_utmp != -1) close(fd_utmp);
}

