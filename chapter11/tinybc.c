//
// Created by 王琛超 on 2020/2/21.
//

#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>

#define oops(m, x) {perror(m); exit(x);}

void be_dc(int *, int *);
void be_bc(int *, int *);
int main() {
    int pid, todc[2], fromdc[2];
    if (pipe(todc) == -1 || pipe(fromdc) == -1) {
        oops("pipe", 1);
    }
    if ((pid = fork()) == -1) {
        oops("fork", 1);
    }
    if (pid == 0) {
        be_dc(todc, fromdc);
    } else {
        be_bc(todc, fromdc);
        wait(NULL);
    }
}

// child
void be_dc(int in[2], int out[2]) {
    // set up stdin to pipein
    if (dup2(in[0],0) == -1)
        oops("dc read", 3);
    close(in[0]);
    close(in[1]);

    // set up stdout to pipeout
    if (dup2(out[1], 1) == -1)
        oops("dc write", 4);
    close(out[1]);
    close(out[0]);

    execlp("dc", "dc", "-", NULL);
    oops("cannot run dc",5);
}

void be_bc(int todc[2], int fromdc[2]) {
    int num1, num2;
    char operation[BUFSIZ], message[BUFSIZ];
    FILE *fpout, *fpin;

    close(todc[0]);
    close(fromdc[1]);

    fpout = fdopen(todc[1], "w");
    fpin = fdopen(fromdc[0], "r");
    if (fpout == NULL || fpin == NULL){
        oops("error convering pipes to streams", 1);
    }
    while (printf("tinybc:"),fgets(message, BUFSIZ, stdin) != NULL) {
        if (sscanf(message, "%d%[-+*/^]%d", &num1, operation, &num2) != 3) {
            printf("syntax error\n");
            continue;
        }
        // 后缀表达式的方式写入到bc的写入端, 这里的p是用于将堆栈中的数据弹出进行计算的。
        if (fprintf(fpout, "%d\n%d\n%c\np\n", num1, num2, *operation) == EOF) {
            oops("error writing",1);
        }
        fflush(fpout);
        if (fgets(message, BUFSIZ, fpin) == NULL)
            break;
        printf("%d %c %d = %s", num1, *operation, num2, message);
    }
    fclose(fpout);
    fclose(fpin);
}