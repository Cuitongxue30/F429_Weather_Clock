#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "com_debug.h"

typedef enum
{
    KEY_NONE = 0,
    KEY0,
    KEY1,
    KEY2,
} KeyNumEnum;

typedef enum
{
    KEY_STATE_IDLE = 0,
    KEY_STATE_DEBOUNCE,
    KEY_STATE_PRESSED,
    KEY_STATE_WAIT_UP
} KeyState_t;

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t active_level;
    KeyState_t state;
    uint8_t id;
} Button_t;

#define BUTTON_COUNT (sizeof(Buttonlist) / sizeof(Button_t))

uint8_t Button_Process_Single(Button_t *button);
uint8_t Key_Scan_All(void);
void Key_Init(void);

#endif
