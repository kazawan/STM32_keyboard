#ifndef KEY_H
#define KEY_H
#include "stm32f1xx_hal.h"
#include "main.h"
#include "gpio.h"
#include "usb_key_define.h"
#define _weak___ __attribute__((weak))

//! OUTPUT  到 INPUT 在开关input那边放一个二极管 1n4148
//! Row 使用输出OUTPUT PP 
//! Col 使用输入 INPUT PULL_DOWN
//todo     c1   c2   c3   c4
//todo r1 1 -> 2 -> 3 -> 4
//todo 




#define ROW_NUM 5
#define COL_NUM 14

typedef struct
{
    char key;
} KEY_MAP;

enum 
{
    idle,
    press,
    release,
}KEY_STATE;

typedef struct
{
    char *key_value;
    int key_index;
    int KEY_STATE;
    unsigned long long time;
    // unsigned long debounce_time;
    int buffer_index;
}KEY_typedef;


typedef struct
{
    int fn_key_state;
    unsigned long long fn_key_time;
    int layer;
}FN_KEY_typedef;



// output
#define Row_1_Pin GPIO_PIN_7 // port b
#define Row_2_Pin GPIO_PIN_8 // port b
#define Row_3_Pin GPIO_PIN_2 // port a
#define Row_4_Pin GPIO_PIN_1 // port a
#define Row_5_Pin GPIO_PIN_0 // port a

#define Row_1_GPIO_Port ROW1_GPIO_Port
#define Row_2_GPIO_Port ROW2_GPIO_Port
#define Row_3_GPIO_Port ROW3_GPIO_Port
#define Row_4_GPIO_Port ROW4_GPIO_Port
#define Row_5_GPIO_Port ROW5_GPIO_Port

// input
#define Col_1_Pin GPIO_PIN_0 // port b
#define Col_2_Pin GPIO_PIN_1 // port b
#define Col_3_Pin GPIO_PIN_10 // port b
#define Col_4_Pin GPIO_PIN_11 // port b

#define Col_5_Pin GPIO_PIN_12 // port b
#define Col_6_Pin GPIO_PIN_13 // port b
#define Col_7_Pin GPIO_PIN_14 // port b
#define Col_8_Pin GPIO_PIN_15 // port b

#define Col_9_Pin GPIO_PIN_8 // port a
#define Col_10_Pin GPIO_PIN_15 // port a
#define Col_11_Pin GPIO_PIN_3 // port b
#define Col_12_Pin GPIO_PIN_4 // port b

#define Col_13_Pin GPIO_PIN_5 // port b
#define Col_14_Pin GPIO_PIN_6 // port b



#define Col_1_GPIO_Port COL1_GPIO_Port
#define Col_2_GPIO_Port COL2_GPIO_Port
#define Col_3_GPIO_Port COL3_GPIO_Port
#define Col_4_GPIO_Port COL4_GPIO_Port

#define Col_5_GPIO_Port COL5_GPIO_Port
#define Col_6_GPIO_Port COL5_GPIO_Port
#define Col_7_GPIO_Port COL5_GPIO_Port
#define Col_8_GPIO_Port COL5_GPIO_Port

#define Col_9_GPIO_Port COL9_GPIO_Port
#define Col_10_GPIO_Port COL9_GPIO_Port
#define Col_11_GPIO_Port COL11_GPIO_Port
#define Col_12_GPIO_Port COL11_GPIO_Port

#define Col_13_GPIO_Port COL11_GPIO_Port
#define Col_14_GPIO_Port COL11_GPIO_Port



// #define row_pin {Row_1_Pin, Row_2_Pin, Row_3_Pin, Row_4_Pin, Row_5_Pin}
// #define col_pin {Col_1_Pin, Col_2_Pin, Col_3_Pin, Col_4_Pin, Col_5_Pin, Col_6_Pin, Col_7_Pin, Col_8_Pin, Col_9_Pin, Col_10_Pin, Col_11_Pin, Col_12_Pin, Col_13_Pin, Col_14_Pin}
// #define row_port {Row_1_GPIO_Port, Row_2_GPIO_Port, Row_3_GPIO_Port, Row_4_GPIO_Port, Row_5_GPIO_Port}
// #define col_port {Col_1_GPIO_Port, Col_2_GPIO_Port, Col_3_GPIO_Port, Col_4_GPIO_Port, Col_5_GPIO_Port, Col_6_GPIO_Port, Col_7_GPIO_Port, Col_8_GPIO_Port, Col_9_GPIO_Port, Col_10_GPIO_Port, Col_11_GPIO_Port, Col_12_GPIO_Port, Col_13_GPIO_Port, Col_14_GPIO_Port}



void KEY_INIT(int num, KEY_typedef *key_typedef, KEY_MAP *key_map);
void key_process(int i ,int state,KEY_typedef *key_typedef);
int find_buff_emtpy_index(uint8_t *sendBuffer, int key_buffer_size);
void key_buffer_insert(int buffer_index, int i, KEY_MAP *key_value, uint8_t *sendBuffer);
void remove_buff(int buff_index, uint8_t *sendBuffer);


_weak___ void key_handler(int i);
_weak___ void key_handler_release(int i);

void key_scan(KEY_typedef *key_typedef);

void FN_KEY_INIT(FN_KEY_typedef *fn_key_typedef);
void FN_KEY_SCAN(FN_KEY_typedef *fn_key_typedef);
void FN_KEY_PROCESS(FN_KEY_typedef *fn_key_typedef);

_weak___ void fn_key_handler();
_weak___ void fn_key_handler_release();

#endif