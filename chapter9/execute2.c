#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include	"varlib.h"
/* execute2.c - includes environmment handling */

int execute(char *argv[])
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors
 */
{
    extern char **environ;
    int	pid ;
    int	child_info = -1;

    if ( argv[0] == NULL )		/* nothing succeeds	*/
        return 0;

    if ( (pid = fork())  == -1 )
        perror("fork");
    else if ( pid == 0 ){
        // 创建子进程的时候将当前父进程表中的内容复制到环境中，以传递给子进程
        environ = VLtable2environ();
        // 子进程相应信号，但是父进程屏蔽，为了保证子进程退出后shell不会退出
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        execvp(argv[0], argv);
        perror("cannot execute command");
        exit(1);
    }
    else {
        if ( wait(&child_info) == -1 )
            perror("wait");
    }
    // 这里子进程成功执行，因此返回状态为0
    printf("%d\n", child_info); // 这里为什么会返回0？
    return child_info;
}