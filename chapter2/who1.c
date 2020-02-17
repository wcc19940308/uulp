//
// Created by 王琛超 on 2020/1/31.
//

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmpx.h>
#include <time.h>

#define SHOWHOST
void show_info(struct utmp*);
void show_time(time_t);
extern int utmp_open(char*);
extern void utmp_close();
extern struct utmp* utmp_next();
extern int umpt_reload();

int main() {
    struct utmp *utbufp;
    if (utmp_open(UTMP_FILE) == -1) {
        perror(UTMP_FILE);
        _exit(1);
    }
    while ((utbufp = utmp_next()) != ((struct utmp*)NULL))
        show_info(utbufp);
    utmp_close();
    return 0;
}

void show_time(time_t timeval) {
    char *cp;
    cp = ctime(&timeval);
    printf("% 12.12s", cp + 4);
}

void show_info(struct utmp *utbufp) {
    // 不显示没登录的用户
    if (utbufp->ut_type != USER_PROCESS)
        return;
    printf("% -8.8s", utbufp->ut_name);
    printf(" ");
    printf("% -8.8s", utbufp->ut_line);
    printf(" ");
    show_time(utbufp->ut_time);
    printf(" ");
    #ifdef SHOWHOST
    printf("( %s)", utbufp->ut_host);
    #endif
    printf("\n");
}

