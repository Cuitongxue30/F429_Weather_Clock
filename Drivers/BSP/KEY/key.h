#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "com_debug.h"

typedef enum
{
    KEY_NONE_EVENT = 0,
    KEY_EVENT_CONFIRM,
    KEY_EVENT_CANCEL,
    KEY_EVENT_UP,
    KEY_EVENT_DOWN,
    KEY_EVENT_ON,
    KEY_EVENT_OFF,
} KeyEvent_t;

typedef enum
{
    MODE_TRIGGRR_UP = 0, // 释放触发
    MODE_TRIGGRR_DOWN,   // 按下触发
    MODE_LONG_PRESS,     // 长按触发
    MODE_TOGGLE_SWITCH   // 切换开关模式
} KeyMode_t;

typedef enum
{
    KEY_STATE_IDLE = 0,     // 空闲状态
    KEY_STATE_DEBOUNCE,     // 消抖状态
    KEY_STATE_PRESSED,      // 按下状态
    KEY_STATE_WAIT_RELEASE, // 等待释放状态
} KeyState_t;

typedef struct
{
    GPIO_TypeDef *port;    //* GPIO端口 */
    uint16_t pin;          //* GPIO引脚 */
    uint8_t active_level;  //* 有效电平 */
    KeyState_t state;      //* 按键状态 */
    uint32_t time;         //* 计时器 */
    KeyMode_t mode;        //* 按键模式 */
    uint8_t id_shortEvent; //* 短按事件ID */
    uint8_t id_longEvent;  //* 长按事件ID */
} Button_t;

#define BUTTON_COUNT (sizeof(Buttonlist) / sizeof(Button_t))
#define PRESS_THRESHOLD 50

uint8_t Button_Process_Single(Button_t *button);
uint8_t Key_Scan_All(void);
void Key_Init(void);

#endif
