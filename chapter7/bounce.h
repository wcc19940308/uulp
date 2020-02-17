//
// Created by 王琛超 on 2020/2/13.
//

#ifndef C_CODING_BOUNCE_H
#define C_CODING_BOUNCE_H

#define BLANK ' '
#define DFL_SYMBOl 'o'
#define BOARD "----------"
#define TOP_ROW 5
#define BOT_ROW 20
#define LEFT_EDGE 10
#define RIGHT_EDGE 70
#define X_INIT 10
#define Y_INIT 10
#define TICKS_PER_SEC 50

// 时间片计数
#define X_TTM 5
#define Y_TTM 8

// 计时器当前值ttg，间隔值ttm,x和y轴各一个计时器
struct ppball {
    int     x_pos, y_pos,
            x_ttg, y_ttg,
            x_ttm, y_ttm,
            x_dir, y_dir;

    char symbol; // 球的符号表示
};

struct board {
    int row, col;
}
;


#endif //C_CODING_BOUNCE_H
