/********************************************
 *@Func: C51��β�͵���ˮ��
 *@Author: ��̼���������@Bվ
 *@Date: 2023.9.12
 *@Description: https://www.bilibili.com/video/BV1Jk4y1w7cz
                ʹ������STC89������
 *********************************************/
#include <reg52.h>
#include <string.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define N 16
typedef unsigned char uint8_t;

/*
������������ÿ��Ԫ�ص�ֵ������LED��ռ�ձȣ�0��0%��Ϊ�����ߵ�ƽ������100��100%��Ϊ�����͵�ƽ����״̬
ֵ�Ӵ�С��ӦLED��������  ����Щֵ���Ҹ�������Ч�����õģ���Ϊ�������תIO����ռ�ձȣ�ռ�ձ�Ҳʮ�ֲ���ȷ
��Ϊ���й���������������Ч����������������ֻ�ǳ�ʼֵ��
��ʼֵ��ÿ��ѭ����ʼ����������duties��ͷ����������ָ���ֵ
���������С��16����ledֻ��8����ֻ��ʾ�����ǰ�˸�������˸�λ��ֻ��Ϊ�˸��ƶ���ʾ����
ͨ���ƶ��������ݣ���ȫ��Ϩ�𣬵�����ʾ��ͬ����
*/
uint8_t code strip_init_left[N] = {0, 0, 0, 0, 0, 0, 0, 0, 100, 50, 25, 12, 6, 3, 1, 0};
uint8_t code strip_init_right[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 12, 25, 50, 100};
uint8_t duties[N];
uint8_t duties_left[N];
uint8_t duties_right[N];

/*����ռ�ձ�����*/
void shift_right_strip(uint8_t *buf, uint8_t len) {
    uint8_t i, t = buf[len-1];
    for(i = len-1; i > 0; i--) {
        buf[i] = buf[i-1];
    }
    buf[0] = t;
}
/*����ռ�ձ�����*/
void shift_left_strip(uint8_t *buf, uint8_t len) {
    uint8_t i, n = len-1, t = buf[0];
    for(i=0; i<n; i++) {
        buf[i] = buf[i+1];
    }
    buf[n] = t;
}
/*����duties_left, ����duties_right�������������ϲ���duties��*/
void shift_center_strip() {
    uint8_t i;
    shift_left_strip(duties_left, N);
    shift_right_strip(duties_right, N);
    for(i=0; i<N; i++) {
        duties[i] = MAX(duties_left[i], duties_right[i]);
    }
}

/*��ʾ��ˮ�ƣ���תIOģ��ռ�ձȣ�cycle��ѭ��������cycleԽ������һ��ʱ����Խ��
values��ռ�ձ����ݣ����forѭ��100�Σ��൱��ռ�ձȰٷ�֮���ķ�ĸ��100��i��values[j]�Ƚϣ�
���i>=values[j],��IO����ߵ�ƽ�ر�LED����������͵�ƽ����LED��
����values[j]��40����ô100��ѭ����ǰ40��ѭ�����ǵ͵�ƽ����LED��
��60��ѭ�����Ǹߵ�ƽ�ر�LED���ﵽռ�ձ�40%������Ч����
���forѭ���Ƿֱ���ÿһ��IO��ռ�ձȣ�һ��8����valueһ��8λ��ÿһλ�ĸߵͶ�Ӧһ��LED��״̬��
*/
void update_leds(uint8_t cycle, uint8_t *values) {
    uint8_t i, j, value;
    while(cycle--) {
        for(i=0; i<100; i++) {
            value = 0; // Ĭ����0������״̬
            for(j=0; j<8; j++) {
                if (i >= values[j]) { // ���i����ռ�ձ���ֵ
                    value |= (1<<j);  // ����1��Ӧλ��values[0~7]��ӦBIT0~BIT7
                }
            }
            P2 = value;
        }
    }
}

void main() {
    uint8_t i;
    while(1) {
        // ����memcpy���ǻָ�led�ĳ�ʼ״̬��8��LEDȫ��
        memcpy(duties, strip_init_right, N);
        // ���ƣ���LED�������
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
