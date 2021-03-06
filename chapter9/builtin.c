/* builtin.c
 * contains the switch and the functions for builtin commands
 */

#include	<stdio.h>
#include	<string.h>
#include	<ctype.h>
#include	"smsh.h"
#include	"varlib.h"

int assign(char *);
int okname(char *);

// 判断set，赋值，export三种内置命令
int builtin_command(char **args, int *resultp)
/*
 * purpose: run a builtin command
 * returns: 1 if args[0] is builtin, 0 if not
 * details: test args[0] against all known builtins.  Call functions
 */
{
    int rv = 0;

    // set显示所有的变量，其中已经export的用*表示
    if (strcmp(args[0], "set") == 0) {
        /* 'set' command? */
        VLlist();
        *resultp = 0;
        rv = 1;
    } else if (strchr(args[0], '=') != NULL) {   /* assignment cmd */
        *resultp = assign(args[0]);
        if (*resultp != -1)            /* x-y=123 not ok */
            rv = 1;
    } else if (strcmp(args[0], "export") == 0) {
        if (args[1] != NULL && okname(args[1]))
            *resultp = VLexport(args[1]);
        else
            *resultp = 1;
        rv = 1;
    }
    return rv;
}

int assign(char *str)
/*
 * purpose: execute name=val AND ensure that name is legal
 * returns: -1 for illegal lval, or result of VLstore
 * warning: modifies the string, but retores it to normal
 */
{
    char *cp;
    int	rv ;

    // 将name=val的形式的字符串分开。
    cp = strchr(str,'=');
    *cp = '\0';
    // 如果名字合法就进行存表
    rv = (okname(str) ? VLstore(str, cp + 1) : -1);
    *cp = '=';
    return rv;
}

// C语言中要求变量名必须为字母，数字或者下划线,且第一位不能是数字
int okname(char *str)
/*
 * purpose: determines if a string is a legal variable name
 * returns: 0 for no, 1 for yes
 */
{
    char *cp;

    for (cp = str; *cp; cp++) {
        if ((isdigit(*cp) && cp == str)
            || !(isalnum(*cp) || *cp == '_'))
            return 0;
    }
    // 如果是空字符串则返回0
    return (cp != str);    /* no empty strings, either */
}