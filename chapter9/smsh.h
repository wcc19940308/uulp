//
// Created by 王琛超 on 2020/2/17.
//

#ifndef C_CODING_SMSH_H
#define C_CODING_SMSH_H

#define YES 1
#define NO 0

char *next_cmd(char *, FILE *);

char **splitline(char*);

void freelist(char **);

void *emalloc(size_t);
void *erealloc(void *, size_t);

int execute(char **);

void fatal(char *, char *, int);

int process();

#endif; //C_CODING_SMSH_H
