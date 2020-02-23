//
// Created by 王琛超 on 2020/2/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "smsh.h"

char *next_cmd(char *prompt, FILE *fp) {
    char *buf;
    int bufspace = 0;
    int pos = 0;
    int c;
    printf("%s", prompt);
    while ((c = getc(fp)) != EOF) {
        if (pos + 1 >= bufspace) {
            if (bufspace == 0) {
                buf = emalloc(BUFSIZ);
            } else {
                // 重新分配更长的缓冲区
                buf = erealloc(buf, bufspace + BUFSIZ);
            }
            bufspace += BUFSIZ;
        }
        if (c == '\n')
            break;
        buf[pos++] = c;
    }
    if (c == EOF && pos == 0)
        return NULL;
    buf[pos] = '\0';
    return buf; // 这里是malloc的，所以可以返回
}

#define is_delim(x) ((x) == ' ' || (x) == '\t')

// 这其实就是一个简版的java的split
char **splitline(char *line) {

    char *newstr();
    char **args;
    int spots = 0;
    int bufspace = 0;
    int argnum = 0;
    char *cp = line;
    char *start;
    int len;

    if (line == NULL)
        return NULL;

    // 分配完后的内存返回给一个二级指针,用于存储传给execvp的字符串数组
    // 二级指针中的每个槽都是一个一级指针char*，每个槽用于存储分配好的"字符串"
    args = emalloc(BUFSIZ);
    bufspace = BUFSIZ;
    spots = BUFSIZ / sizeof(char *);

    // 对输入的命令进行切分
    while (*cp != '\0') {
        while (is_delim(*cp))
            cp++;
        if (*cp == '\0')
            break;
        // execvp调用要求最后一位为NULL
        if (argnum + 1 >= spots) {
            args = erealloc(args, bufspace + BUFSIZ);
            bufspace += BUFSIZ;
            spots += (BUFSIZ / sizeof(char *));
        }
        // 根据空格切分，找到每段的起始位置，分配内存
        start = cp;
        len = 1;
        while (*++cp != '\0' && !(is_delim(*cp)))
            len++;
        args[argnum++] = newstr(start, len);
    }
    // execvp的调用要求最后一位是NULL
    args[argnum] = NULL;
    return args;
}

char *newstr(char *s, int l) {
    char *rv = emalloc(l + 1);
    rv[l] = '\0';
    strncpy(rv,s,l);
    return rv;
}

void freelist(char **list) {
    char **cp = list;
    // 释放二级指针所指向的每个槽所指向的空间
    while (*cp)
        free(*cp++);
    // 释放二级指针指向的所有槽的空间
    free(list);
}

void *emalloc(size_t n) {
    void *rv;
    // 这边的rv是在堆上分配的内存，因此返回的指针有效
    if ((rv = malloc(n)) == NULL)
        fatal("out of memory", "", 1);
    return rv;
}

void *erealloc(void *p, size_t n) {
    void *rv;
    if ((rv = realloc(p,n) == NULL))
        fatal("realloc() failed", "", 1);
    return rv;
}
