#include "key.h"

Button_t Buttonlist[] = {
    {KEY0_GPIO_Port, KEY0_Pin, GPIO_PIN_RESET, KEY_STATE_IDLE, KEY0},
    {KEY1_GPIO_Port, KEY1_Pin, GPIO_PIN_RESET, KEY_STATE_IDLE, KEY1},
    {KEY2_GPIO_Port, KEY2_Pin, GPIO_PIN_RESET, KEY_STATE_IDLE, KEY2},
};

void Key_Init(void)
{
}

uint8_t Button_Process_Single(Button_t *button)
{
    uint8_t current_level = HAL_GPIO_ReadPin(button->port, button->pin);
    uint8_t is_pressed = (current_level == button->active_level);
    uint8_t return_id = 0;

    switch (button->state)
    {
    case KEY_STATE_IDLE:
        if (is_pressed)
        {
            button->state = KEY_STATE_DEBOUNCE;
        }
        break;
    case KEY_STATE_DEBOUNCE:
        if (is_pressed)
        {
            button->state = KEY_STATE_PRESSED;
        }
        else
        {
            button->state = KEY_STATE_IDLE;
        }
        break;
    case KEY_STATE_PRESSED:
        if (!is_pressed)
        {
            button->state = KEY_STATE_IDLE;
            return_id = button->id;
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
