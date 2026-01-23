/**
 * @file BSP_dht11.h
 * @author Antares (cuitongxue30@gmail.com)
 * @brief DHT11驱动
 * @version 0.1
 * @date 2026-01-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef __BSP_DHT11_H
#define __BSP_DHT11_H

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "com_debug.h"

#define DHT11_DATA_H HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET)
#define DHT11_DATA_L HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_RESET)
#define DHT11_DATA_READ HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)

void DHT11_Init(void);
uint8_t DHT11_Read_Data(int8_t *temperature, int8_t *humidity);


#endif // __BSP_DHT11_H
