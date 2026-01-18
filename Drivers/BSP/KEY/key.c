#include "key.h"

Button_t Buttonlist[] = {
    /*端口, 引脚, 有效电平, 状态, 计时器,  模式,  短按事件, 长按事件*/
    {KEY0_GPIO_Port, KEY0_Pin, GPIO_PIN_RESET, KEY_STATE_IDLE, 0, MODE_TRIGGRR_UP, KEY_EVENT_UP, 0},
    {KEY1_GPIO_Port, KEY1_Pin, GPIO_PIN_RESET, KEY_STATE_IDLE, 0, MODE_TRIGGRR_DOWN, KEY_EVENT_DOWN, 0},
    {KEY2_GPIO_Port, KEY2_Pin, GPIO_PIN_RESET, KEY_STATE_IDLE, 0, MODE_LONG_PRESS, KEY_EVENT_CONFIRM, KEY_EVENT_CANCEL},
};

void Key_Init(void)
{
}

uint8_t Button_Process_Single(Button_t *button)
{
    uint8_t current_level = HAL_GPIO_ReadPin(button->port, button->pin);
    uint8_t is_pressed = (current_level == button->active_level);
    uint8_t return_id = 0;

    if (button->mode == MODE_TOGGLE_SWITCH)
    {
        // static last_state = 0;
        // if (is_pressed && !last_state)
        // {
        // }
        return 0;
    }

    switch (button->state)
    {
    case KEY_STATE_IDLE:
        if (is_pressed)
        {
            button->state = KEY_STATE_DEBOUNCE;
            button->time = 0;
        }
        break;
    case KEY_STATE_DEBOUNCE:
        if (is_pressed)
        {
            button->state = KEY_STATE_PRESSED;
            if (button->mode == MODE_TRIGGRR_DOWN)
            {
                return_id = button->id_shortEvent;
            }
        }
        else
        {
            button->state = KEY_STATE_IDLE;
        }
        break;
    case KEY_STATE_PRESSED:
        if (is_pressed)
        {
            if (button->mode == MODE_LONG_PRESS)
            {
                button->time++;
                if (button->time >= PRESS_THRESHOLD)
                {
                    return_id = button->id_longEvent;
                    button->state = KEY_STATE_WAIT_RELEASE;
                }
            }
        }
        else
        {
            if (button->mode == MODE_TRIGGRR_UP)
            {
                return_id = button->id_shortEvent;
            }
            else if (button->mode == MODE_LONG_PRESS)
            {
                if (button->time <= PRESS_THRESHOLD)
                {
                    return_id = button->id_shortEvent;
                }

                return_id = button->id_shortEvent;
            }
            button->state = KEY_STATE_IDLE;
        }
        break;
    case KEY_STATE_WAIT_RELEASE:
        if (!is_pressed)
        {
            button->state = KEY_STATE_IDLE;
        }
        break;
    }
    return return_id;
}

uint8_t Key_Scan_All(void)
{
    uint8_t event = 0;
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        event = Button_Process_Single(&Buttonlist[i]);
        if (event != 0)
        {
            return event;
        }
    }
    return 0;
}
