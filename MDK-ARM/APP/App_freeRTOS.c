#include "App_freeRTOS.h"

TaskHandle_t Task1Handle;
TaskHandle_t Task2Handle;

int8_t temperature = 0;
int8_t humidity = 0;

/**
 * @brief 启动FreeRTOS
 *
 */
void App_FreeRTOS_Start(void)
{
    // xTaskCreate(task1, "Task1", 128, NULL, 1, &Task1Handle);
    // xTaskCreate(task2, "Task2", 128, NULL, 2, &Task2Handle);
    // xTaskCreate(vtask_KeyScan, "KeyScan", 128, NULL, 3, NULL);
    xTaskCreate(vtask_Dht11, "Dht11", 128, NULL, 3, NULL);

    vTaskStartScheduler();
}

void task1(void *pvParameters)
{
    for (;;)
    {
        DEBUG_PRINT("task1 print\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task2(void *pvParameters)
{
    for (;;)
    {
        DEBUG_PRINT("Hello FreeRTOS World 2222!\r\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vtask_KeyScan(void *pvParameters)
{
    for (;;)
    {
        uint8_t key_event = Key_Scan_All();
        if (key_event != 0)
        {
            DEBUG_PRINT("Key Event: %d\r\n", key_event);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void vtask_Dht11(void *pvParameters)
{
    DHT11_Init();
    uint8_t task_collect_count = 9;
    for (;;)
    {
        task_collect_count++;
        if (task_collect_count >= 10)
        {
            task_collect_count = 0;
            DHT11_Read_Data(&temperature, &humidity);
            DEBUG_PRINT("Temperature: %d C, Humidity: %d %%\r\n", temperature, humidity);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
