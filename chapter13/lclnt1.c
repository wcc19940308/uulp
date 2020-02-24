//
// Created by 王琛超 on 2020/2/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

int setup();
int get_ticket();
void do_regular_work();
void release_ticket();
void shut_down();
int validate_ticket();
/**
 * setup和shut_down处理网络资源，中间部分用于业务处理
 * get_ticket和release_ticket产生request通过do_transaction进行sendto，同时从do_transaction
 * 接收response进行结果的查看
 */

int main(int argc, char **argv) {
    setup();
    if (get_ticket() != 0)
        exit(0);
    do_regular_work();
    release_ticket();
    shut_down();
}

void do_regular_work() {
    printf("SuperSleep version 1.0 Running - Licensed Software\n");
    sleep(15);
    // 客户端同时周期性验证
    if (validate_ticket() != 0) {
        printf("Server errors.");
        return;
    }
    sleep(15);
}