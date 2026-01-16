/**
 * @file com_debug.h
 * @author Antares (cuitongxue30@gmail.com)
 * @brief 日志打印输出
 * @version 0.1
 * @date 2026-01-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef COM_DEBUG_H
#define COM_DEBUG_H

#include "usart.h"
#include "stdio.h"
#include "stdarg.h"

#define DEBUG_ENABLE 1
#ifdef DEBUG_ENABLE
#define DEBUG_PRINT(format, ...) printf("[%s:%d]" format "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif
#endif // COM_DEBUG_H
