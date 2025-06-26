/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-24     liuxin       the first version
 */
#include "drv_hwtimer.h"

#define DBG_TAG "timer"
#define DBG_LVL DBG_LOG    // 确保是 DBG_LOG 或更高
#include <rtdbg.h>

//TIM时钟频率取决于APB1/APB2和倍频器系数
#define TIM_APB_PPL 2

#define CLOCK_HZ 120*1000000U

enum
{
#ifdef BSP_USING_TIM1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_TIM2
TIM2_INDEX,
#endif
#ifdef BSP_USING_TIM3
TIM3_INDEX,
#endif
#ifdef BSP_USING_TIM4
TIM4_INDEX,
#endif
#ifdef BSP_USING_TIM5
TIM5_INDEX,
#endif
#ifdef BSP_USING_TIM6
TIM6_INDEX,
#endif
#ifdef BSP_USING_TIM7
TIM7_INDEX,
#endif
#ifdef BSP_USING_TIM8
TIM8_INDEX,
#endif
#ifdef BSP_USING_TIM9
TIM9_INDEX,
#endif
#ifdef BSP_USING_TIM10
TIM10_INDEX,
#endif
#ifdef BSP_USING_TIM11
TIM11_INDEX,
#endif
#ifdef BSP_USING_TIM12
TIM12_INDEX,
#endif
#ifdef BSP_USING_TIM13
TIM13_INDEX,
#endif
#ifdef BSP_USING_TIM14
TIM14_INDEX,
#endif
#ifdef BSP_USING_TIM15
TIM15_INDEX,
#endif
#ifdef BSP_USING_TIM16
TIM16_INDEX,
#endif
#ifdef BSP_USING_TIM17
TIM17_INDEX,
#endif
};

struct gd32_hwtimer timers[] = {
#ifdef BSP_USING_TIM1
    { .clk = RCU_TIMER1, .tim_periph = TIMER1, .name = "timer1", .type = TIMER_TYPE_L0, .irq = TIMER1_IRQn }
#endif

#ifdef BSP_USING_TIM2
    {
        .clk = RCU_TIMER2,
        .tim_periph = TIMER2,
        .name = "timer2",
        .type = TIMER_TYPE_L0,
        .irq = TIMER2_IRQn
    }
#endif
#ifdef BSP_USING_TIM3
    {
        .clk = RCU_TIMER3,
        .tim_periph = TIMER3,
        .name = "timer3",
        .type = TIMER_TYPE_L0,
        .irq = TIMER3_IRQn
    }
#endif
#ifdef BSP_USING_TIM4
    {
        .clk = RCU_TIMER4,
        .tim_periph = TIMER4,
        .name = "timer4",
        .type = TIMER_TYPE_L0,
        .irq = TIMER4_IRQn
    }
#endif
};

void __init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
gd32_hwtimer_t *tim = (gd32_hwtimer_t*) timer;
if (state)
{
    rcu_periph_clock_enable(tim->clk);
    timer_parameter_struct tim_init;
    tim_init.period = 10000 - 1;
    tim_init.clockdivision = TIMER_CKDIV_DIV1;
    tim_init.prescaler = (uint16_t) (rcu_clock_freq_get(CK_APB1) * TIM_APB_PPL / 10000) - 1;
    if (timer->info->cntmode == HWTIMER_CNTMODE_UP)
    {
        tim_init.counterdirection = TIMER_COUNTER_UP;
    }
    else
    {
        tim_init.counterdirection = TIMER_COUNTER_DOWN;
    }
    tim_init.alignedmode = TIMER_COUNTER_EDGE;
    timer_init(tim->tim_periph, &tim_init);
    timer_interrupt_flag_clear(tim->tim_periph, TIMER_INT_UP);
    nvic_irq_enable(tim->irq, 0, 0);
    timer_interrupt_enable(tim->tim_periph, TIMER_INT_UP);
}
else
{
    nvic_irq_disable(tim->irq);
    timer_interrupt_disable(tim->tim_periph, TIMER_INT_UP);
    timer_deinit(tim->tim_periph);
}
}

rt_err_t start(struct rt_hwtimer_device *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
gd32_hwtimer_t *tim = (gd32_hwtimer_t*) timer;
timer_autoreload_value_config(tim->tim_periph, cnt);
if (mode == HWTIMER_MODE_ONESHOT)
{
    timer_single_pulse_mode_config(tim->tim_periph, TIMER_SP_MODE_SINGLE);
}
else
{
    timer_single_pulse_mode_config(tim->tim_periph, TIMER_SP_MODE_REPETITIVE);
}
timer_counter_value_config(tim->tim_periph, 0);
timer_enable(tim->tim_periph);
return RT_EOK;
}

void stop(struct rt_hwtimer_device *timer)
{
gd32_hwtimer_t *tim = (gd32_hwtimer_t*) timer;
timer_disable(tim->tim_periph);
timer_counter_value_config(tim->tim_periph, 0);
}

rt_uint32_t count_get(struct rt_hwtimer_device *timer)
{
gd32_hwtimer_t *tim = (gd32_hwtimer_t*) timer;
return timer_counter_read(tim->tim_periph);
}
rt_err_t control(struct rt_hwtimer_device *timer, rt_uint32_t cmd, void *args)
{
gd32_hwtimer_t *tim = (gd32_hwtimer_t*) timer;
switch (cmd)
{
case HWTIMER_CTRL_FREQ_SET:
{
    uint32_t freq;
    uint16_t psc;
    freq = *(uint32_t*) args;
    psc = rcu_clock_freq_get(CK_APB1) / freq * TIM_APB_PPL;
    timer_prescaler_config(tim->tim_periph, psc - 1, TIMER_PSC_RELOAD_NOW);
    //rcu_timer_clock_prescaler_config(timer_clock_prescaler)
}
    break;
default:
    break;
}
return RT_EOK;
}

struct rt_hwtimer_ops __ops = { __init, start, stop, count_get, control };

struct rt_hwtimer_info L0_info = {
CLOCK_HZ, /* the maximum count frequency timer support */
CLOCK_HZ / 0xFFFF, /* the minimum count frequency timer support */
0xFFFF, /* counter maximum value */
HWTIMER_CNTMODE_UP /* count mode (inc/dec) */
};

void rt_hw_timer_init()
{

for (uint8_t i = 0; i < sizeof(timers) / sizeof(timers[0]); i++)
{
    gd32_hwtimer_t *tim = &timers[i];
    tim->tim.ops = &__ops;
    switch (tim->type)
    {
    case TIMER_TYPE_L0:
        tim->tim.info = &L0_info;
        break;
    }
    if (rt_device_hwtimer_register((rt_hwtimer_t*) tim, tim->name, RT_NULL) == RT_EOK)
    {
        LOG_D("%s register success", tim->name);
    }
    else
    {
        LOG_E("%s register failed", tim->name);
    }
}
}
INIT_APP_EXPORT(rt_hw_timer_init);
//INIT_BOARD_EXPORT(rt_hw_timer_init);

void TIMER1_IRQHandler(void)
{
rt_interrupt_enter();
rt_device_hwtimer_isr(&timers[TIM1_INDEX].tim);
timer_interrupt_flag_clear(timers[TIM1_INDEX].tim_periph, TIMER_INT_UP);
rt_interrupt_leave();
}

