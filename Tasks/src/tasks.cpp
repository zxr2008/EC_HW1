/**
 * @file    tasks.cpp
 * @brief   电控第一次作业：GPIO 点灯（第 1 题）、1 ms 定时器更新中断（第 2 题）、
 *          IWDG 喂狗（第 2/3 题的差别就在这一行）。
 */

#include "tasks.hpp"

#include "main.h"

/* CubeMX 勾了“Generate peripheral initialization as a pair of .c/.h files”时，
   htim2 / hiwdg 的 extern 声明在 tim.h / iwdg.h 里；没勾时在 main.h 里。
   用 __has_include 两种工程都能编译。 */
#if __has_include("tim.h")
#include "tim.h"
#endif
#if __has_include("iwdg.h")
#include "iwdg.h"
#endif

/* 定时器更新中断里自增的全局计数变量：名字必须叫 tick，类型必须是 volatile uint32_t */
volatile uint32_t tick = 0U;

/* 编译期提示：CubeMX 里必须把这颗 LED 引脚的用户标签（User Label）设成 LED，
   生成的 main.h 里才会有 LED_Pin / LED_GPIO_Port 这两个宏。 */
#ifndef LED_Pin
#error "main.h 里没有 LED_Pin：请在 CubeMX 中把 LED 引脚(User Label)命名为 LED 后重新生成代码"
#endif

void Tasks_Init(void)
{
    /* 第 1 题 GPIO：在初始化里把这颗脚写成表里的电平（低电平，板载灯点亮）。
       不要在 while (1) 里翻转。 */
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

    /* 第 2 题 定时器：启动 TIM2 的更新中断，中断周期 1 ms
       （PSC = 定时器时钟(MHz) - 1，ARR = 999，见说明文档的计算过程）。
       中断服务函数 TIM2_IRQHandler 由 CubeMX 生成在 Core/Src/stm32xxxx_it.c 里，
       它最终会调用下面的 HAL_TIM_PeriodElapsedCallback。 */
    HAL_TIM_Base_Start_IT(&htim2);
}

/**
 * @brief 定时器更新中断回调。全工程只写这一份（放在 Tasks 的源文件里）。
 * @note  用 C++ 编译时必须加 extern "C"，否则和 HAL 里的弱定义对不上，
 *        Ozone/链接阶段会出现重复定义或回调不生效。
 */
extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        tick++;

        /* 第 3 题（看门狗题）：这里不再喂狗。
           第 2 题（定时器题）时这一行是 HAL_IWDG_Refresh(&hiwdg); —— 不喂狗 → 约 2 s 复位一次。 */
    }
}
