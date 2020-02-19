#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include	"smsh.h"

#define	DFL_PROMPT	"> "

int main() {
    char *cmdline, *prompt, **arglist;
    int result, process(char **);
    void setup();

    prompt = DFL_PROMPT;
    setup();

    // 从stdin读，分配缓冲区，然后返回，进行切分，根据不同的输入类型process进行处理
    while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
        if ((arglist = splitline(cmdline)) != NULL) {
            result = process(arglist);
            freelist(arglist);
        }
        free(cmdline);
    }
    return 0;
}

// 父进程忽略信号，子进程以默认方式处理信号
void setup()
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n) {
    fprintf(stderr, "Error: %s,%s\n", s1, s2);
    exit(n);
}