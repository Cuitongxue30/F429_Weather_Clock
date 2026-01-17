/**
 * @file App_freeRTOS.h
 * @author Antares (cuitongxue30@gmail.com)
 * @brief 应用层freeRTOS
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef __APP_FREERTOS_H
#define __APP_FREERTOS_H

#include "FreeRTOS.h"
#include "task.h"
#include "com_debug.h"
#include "key.h"

void task1(void *pvParameters);
void task2(void *pvParameters);
void vtask_KeyScan(void *pvParameters);
/**
 * @brief 启动FreeRTOS
 *
 */
void App_FreeRTOS_Start(void);

#endif // __APP_FREERTOS_H
