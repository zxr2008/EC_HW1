/**
 * @file    tasks.hpp
 * @brief   电控第一次作业：三题业务代码的对外接口。
 * @note    业务代码只写在 Tasks 里；main.c 只在 USER CODE 区包含本头文件并调用 Tasks_Init()。
 */

#ifndef TASKS_HPP
#define TASKS_HPP

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 1 ms 定时器更新中断里自增 1 的全局计数变量。
 * @note  必须是全局的 volatile uint32_t，变量名必须叫 tick，这样 Ozone 的
 *        Watched Data / Timeline 里才能实时看到它（不会被优化掉）。
 */
extern volatile uint32_t tick;

/**
 * @brief 业务初始化：把 LED 引脚写成要求的电平，并启动定时器的更新中断。
 * @note  在 CubeMX 生成的 main.c 中，于 USER CODE BEGIN 2 区调用。
 */
void Tasks_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* TASKS_HPP */
