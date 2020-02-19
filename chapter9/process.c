//
// Created by 王琛超 on 2020/2/18.
//

#include	<stdio.h>
#include	"smsh.h"

int is_control_command(char *); // 命令是脚本语言一部分还是可执行的
int do_control_command(char **); // 处理关键字if,then,fi
int ok_to_execute(); // 能否执行当前命令

int process(char **args)
/*
 * purpose: process user command
 * returns: result of processing command
 * details: if a built-in then call appropriate function, if not execute()
 *  errors: arise from subroutines, handled there
 */
{
    int rv = 0;

    if (args[0] == NULL)
        rv = 0;
    else if (is_control_command(args[0]))
        rv = do_control_command(args);
    else if (ok_to_execute())
        rv = execute(args);
    return rv;
}
