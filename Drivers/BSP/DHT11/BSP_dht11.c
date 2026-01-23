#include "BSP_dht11.h"

uint8_t data[5] = {0};

void Inf_Delay_us(uint32_t us)
{
    uint32_t count = us * 45;
    while (count--)
    {
        __NOP();
    }
}

void DHT11_Init(void)
{
    DHT11_DATA_H;
    vTaskDelay(2000);
}

uint8_t DHT11_Read_Data(int8_t *temperature, int8_t *humidity)
{
    uint8_t i = 0, j = 0;
    uint32_t count_max = 5000;

    for (uint8_t k = 0; k < 5; k++)
        data[k] = 0;
    DHT11_DATA_L;
    vTaskDelay(20);
    DHT11_DATA_H;
    Inf_Delay_us(30);

    while (DHT11_DATA_READ == GPIO_PIN_SET && count_max--)
    {
        Inf_Delay_us(1);
    }
    if (count_max == 0)
    {
        DEBUG_PRINT("DHT11 No Response (High->Low)\r\n");
        return 0;
    }
    while (DHT11_DATA_READ == GPIO_PIN_RESET && count_max--)
    {
        Inf_Delay_us(1);
    }
    if (count_max == 0)
    {
        DEBUG_PRINT("DHT11 No Response (Low->High)\r\n");
        return 0;
    }
    while (DHT11_DATA_READ == GPIO_PIN_SET && count_max--)
    {
        Inf_Delay_us(1);
    }
    if (count_max == 0)
    {
        DEBUG_PRINT("DHT11 No Response (Start Data)\r\n");
        return 0;
    }

    taskENTER_CRITICAL();
    for (i = 0; i < 5; i++)
    {

        for (j = 0; j < 8; j++)
        {
            while (DHT11_DATA_READ == GPIO_PIN_RESET)
            {
            }
            Inf_Delay_us(40);
            data[i] <<= 1;
            if (DHT11_DATA_READ == GPIO_PIN_SET)
            {
                data[i] |= 0x01;
            }
            while (DHT11_DATA_READ == GPIO_PIN_SET)
                ;
        }
    }
    taskEXIT_CRITICAL();

    uint32_t sum = data[0] + data[1] + data[2] + data[3];

    if ((uint8_t)sum != data[4])
    {
        DEBUG_PRINT("DHT11 Checksum Error! Read: %02X %02X %02X %02X | Sum: %02X != %02X\r\n",
                    data[0], data[1], data[2], data[3], (uint8_t)sum, data[4]);
        return 0;
    }

    *humidity = data[0];
    int16_t temp_val = data[2];

    if (data[3] & 0x80)
    {
        temp_val = -temp_val;
    }

    *temperature = temp_val;
    return 1;
}
