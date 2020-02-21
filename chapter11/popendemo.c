//
// Created by 王琛超 on 2020/2/21.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buf[100];
    int i = 0;

    fp = popen("who | sort", "r");
    while (fgets(buf, 100, fp) != NULL) {
        printf("%3d %s", i++, buf);
    }
    pclose(fp);
}