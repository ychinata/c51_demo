/********************************************
 *@Func: C51带尾巴的流水灯
 *@Author: 编程技术与艺术@B站
 *@Date: 2023.9.12
 *@Description: https://www.bilibili.com/video/BV1Jk4y1w7cz
                使用普中STC89开发板
 *********************************************/
#include <reg52.h>
#include <string.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define N 16
typedef unsigned char uint8_t;

/*
下面两个数组每个元素的值是驱动LED的占空比，0（0%）为持续高电平不亮，100（100%）为持续低电平最亮状态
值从大到小对应LED由亮到暗  ，这些值是我根据运行效果设置的，因为是软件翻转IO控制占空比，占空比也十分不精确
因为运行过程中有左移右移效果，下面两个数组只是初始值，
初始值在每次循环开始，给带下面duties开头的三个数组恢复初值
所有数组大小是16个，led只有8个，只显示数组的前八个，后面八个位置只是为了给移动显示服务，
通过移动数组内容，从全部熄灭，到逐渐显示不同亮度
*/
uint8_t code strip_init_left[N] = {0, 0, 0, 0, 0, 0, 0, 0, 100, 50, 25, 12, 6, 3, 1, 0};
uint8_t code strip_init_right[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 12, 25, 50, 100};
uint8_t duties[N];
uint8_t duties_left[N];
uint8_t duties_right[N];

/*右移占空比数组*/
void shift_right_strip(uint8_t *buf, uint8_t len) {
    uint8_t i, t = buf[len-1];
    for(i = len-1; i > 0; i--) {
        buf[i] = buf[i-1];
    }
    buf[0] = t;
}
/*左移占空比数组*/
void shift_left_strip(uint8_t *buf, uint8_t len) {
    uint8_t i, n = len-1, t = buf[0];
    for(i=0; i<n; i++) {
        buf[i] = buf[i+1];
    }
    buf[n] = t;
}
/*左移duties_left, 右移duties_right，最后将两个数组合并到duties里*/
void shift_center_strip() {
    uint8_t i;
    shift_left_strip(duties_left, N);
    shift_right_strip(duties_right, N);
    for(i=0; i<N; i++) {
        duties[i] = MAX(duties_left[i], duties_right[i]);
    }
}

/*显示流水灯，翻转IO模拟占空比，cycle是循环次数，cycle越大，流动一次时间间隔越大
values是占空比数据；外层for循环100次，相当于占空比百分之几的分母是100，i跟values[j]比较，
如果i>=values[j],则IO输出高电平关闭LED，否则输出低电平点亮LED，
比如values[j]是40，那么100次循环中前40次循环就是低电平点亮LED，
后60次循环就是高电平关闭LED，达到占空比40%点亮的效果。
里层for循环是分别处理每一个IO的占空比，一共8个，value一共8位，每一位的高低对应一个LED的状态，
*/
void update_leds(uint8_t cycle, uint8_t *values) {
    uint8_t i, j, value;
    while(cycle--) {
        for(i=0; i<100; i++) {
            value = 0; // 默认是0，点亮状态
            for(j=0; j<8; j++) {
                if (i >= values[j]) { // 如果i大于占空比数值
                    value |= (1<<j);  // 则置1对应位，values[0~7]对应BIT0~BIT7
                }
            }
            P2 = value;
        }
    }
}

void main() {
    uint8_t i;
    while(1) {
        // 以下memcpy都是恢复led的初始状态，8个LED全灭
        memcpy(duties, strip_init_right, N);
        // 右移，让LED逐个点亮
        for(i=0; i<9; i++) {
            shift_right_strip(duties, N);
            update_leds(4, duties);
        }
        memcpy(duties, strip_init_left, N);
        for(i=0; i<9; i++) {
            shift_left_strip(duties, N);
            update_leds(4, duties);
            
        }
        memcpy(duties_left, strip_init_left, N);
        memcpy(duties_right, strip_init_right, N);
        for(i=0; i<15; i++) {
            shift_center_strip();
            update_leds(4, duties);
        }
    }
}
