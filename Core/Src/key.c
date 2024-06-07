#include "key.h"

uint16_t row_pin[ROW_NUM] = {Row_1_Pin, Row_2_Pin, Row_3_Pin, Row_4_Pin, Row_5_Pin};
uint16_t col_pin[COL_NUM] = {Col_1_Pin, Col_2_Pin, Col_3_Pin, Col_4_Pin, Col_5_Pin, Col_6_Pin, Col_7_Pin, Col_8_Pin, Col_9_Pin, Col_10_Pin, Col_11_Pin, Col_12_Pin, Col_13_Pin, Col_14_Pin};
uint32_t row_port[ROW_NUM] = {Row_1_GPIO_Port, Row_2_GPIO_Port, Row_3_GPIO_Port, Row_4_GPIO_Port, Row_5_GPIO_Port};
uint32_t col_port[COL_NUM] = {Col_1_GPIO_Port, Col_2_GPIO_Port, Col_3_GPIO_Port, Col_4_GPIO_Port, Col_5_GPIO_Port, Col_6_GPIO_Port, Col_7_GPIO_Port, Col_8_GPIO_Port, Col_9_GPIO_Port, Col_10_GPIO_Port, Col_11_GPIO_Port, Col_12_GPIO_Port, Col_13_GPIO_Port, Col_14_GPIO_Port};

void KEY_INIT(int num, KEY_typedef *key_typedef, KEY_MAP *key_map)
{
    for (int i = 0; i < num; i++)
    {
        key_typedef[i].key_value = key_map[i].key;
        key_typedef[i].key_index = i;
        key_typedef[i].KEY_STATE = idle;
        key_typedef[i].time = 0;
        key_typedef[i].buffer_index = -1;
    }
}

void key_process(int i, int state, KEY_typedef *key_typedef)
{
    if (state)
    {
        if (key_typedef[i].KEY_STATE == idle)
        {
            key_typedef[i].KEY_STATE = press;
        }
        else if (key_typedef[i].KEY_STATE == press)
        {
            key_typedef[i].KEY_STATE = release;
            // 按键按下 回调函数
            key_handler(i);
        }
    }
    else
    {
        if (key_typedef[i].KEY_STATE == release)
        {
            key_typedef[i].KEY_STATE = idle;
            // 按键释放 回调函数
            key_handler_release(i);
        }
    }
}

int find_buff_emtpy_index(uint8_t *sendBuffer, int key_buffer_size)
{
    uint8_t i;
    int index = -1;

    for (i = 2; i < key_buffer_size; i++) // 循环buff
    {
        if (index == -1)
        {
            if (sendBuffer[i] == 0) // 如果找到一个位置是空的则返回i
            {
                index = i;
                break;
            }
        }
        else
        {
            index = -1;
        }
    }
    return index;
}

void key_buffer_insert(int buffer_index, int i, KEY_MAP *key_value, uint8_t *sendBuffer)
{
    if (buffer_index != -1)
    {
        sendBuffer[buffer_index] = key_value[i].key;
    }
}

void remove_buff(int buff_index, uint8_t *sendBuffer)
{
    sendBuffer[buff_index] = 0x00;
}

void key_scan(KEY_typedef *key_typedef)
{
    uint8_t row, col;
    for (row = 0; row < ROW_NUM; row++)
    {
        // for (int i = 0; i < ROW_NUM; i++)
        // {
        //     HAL_GPIO_WritePin(&row_port[i], row_pin[i], GPIO_PIN_RESET);
        // }
        HAL_GPIO_WritePin(Row_1_GPIO_Port, Row_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_2_GPIO_Port, Row_2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_3_GPIO_Port, Row_3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_4_GPIO_Port, Row_4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_5_GPIO_Port, Row_5_Pin, GPIO_PIN_RESET);

        //! 扫描行 单行输出高电平

        // HAL_GPIO_WritePin(Row_Ports, ROW_1_Pin << row, GPIO_PIN_SET);
        switch (row)
        {
        case 0:
            HAL_GPIO_WritePin(Row_1_GPIO_Port, Row_1_Pin, GPIO_PIN_SET);
            break;
        case 1:
            // HAL_GPIO_WritePin(row_port[row], row_pin[row], GPIO_PIN_SET);
            HAL_GPIO_WritePin(Row_2_GPIO_Port, Row_2_Pin, GPIO_PIN_SET);

            break;
        case 2:
            // HAL_GPIO_WritePin(row_port[row], row_pin[row], GPIO_PIN_SET);
            HAL_GPIO_WritePin(Row_3_GPIO_Port, Row_3_Pin, GPIO_PIN_SET);
            break;
        case 3:
            // HAL_GPIO_WritePin(row_port[row], row_pin[row], GPIO_PIN_SET);
            HAL_GPIO_WritePin(Row_4_GPIO_Port, Row_4_Pin, GPIO_PIN_SET);

            break;
        case 4:
            // HAL_GPIO_WritePin(row_port[row], row_pin[row], GPIO_PIN_SET);
            HAL_GPIO_WritePin(Row_5_GPIO_Port, Row_5_Pin, GPIO_PIN_SET);
            break;
        }
        for (col = 0; col < COL_NUM; col++)
        {
            //! 扫描列 如果该行有按键按下则输出高电平
            if (row * COL_NUM + col > 60)
            {
                break;
            }
            if (HAL_GPIO_ReadPin(col_port[col], col_pin[col]) == GPIO_PIN_SET)
            {
                // todo ....

                key_process(row * COL_NUM + col, 1, key_typedef);
                // input reset
            }
            else
            {
                key_process(row * COL_NUM + col, 0, key_typedef);
            }
        }
        //! 该行扫描完毕 输出低电平
        // HAL_GPIO_WritePin(Row_Ports, ROW_1_Pin << row, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_1_GPIO_Port, Row_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_2_GPIO_Port, Row_2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_3_GPIO_Port, Row_3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_4_GPIO_Port, Row_4_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Row_5_GPIO_Port, Row_5_Pin, GPIO_PIN_RESET);
    }
}

void FN_KEY_INIT(FN_KEY_typedef *fn_key_typedef)
{
    fn_key_typedef->fn_key_state = idle;
    fn_key_typedef->fn_key_time = 0;
    fn_key_typedef->layer = 0;
}

void FN_KEY_SCAN(FN_KEY_typedef *fn_key_typedef)
{
    if(HAL_GPIO_ReadPin(FN_GPIO_Port,FN_Pin) == GPIO_PIN_RESET){
        if(fn_key_typedef->fn_key_state == idle){
            fn_key_typedef->fn_key_state = press;
        }
    }else{
        if(fn_key_typedef->fn_key_state == press){
            fn_key_typedef->fn_key_state = release;
            
        }
    }
}

void FN_KEY_PROCESS(FN_KEY_typedef *fn_key_typedef)
{
    if(fn_key_typedef->fn_key_state == press){
        // fn_key_typedef->layer = 1;
        fn_key_handler();
    }
    if(fn_key_typedef->fn_key_state == release){
        // fn_key_typedef->layer = 0;
        fn_key_typedef->fn_key_state = idle;
        fn_key_handler_release();
    }
}
