/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-24     liuxin       the first version
 */
#ifndef DRIVERS_DRV_HWTIMER_H_
#define DRIVERS_DRV_HWTIMER_H_

#include "board.h"
#include <rtthread.h>
#include "gd32f4xx.h"
#include "rtdevice.h"

typedef enum{
    TIMER_TYPE_L0,
    TIMER_TYPE_L1,
    TIMER_TYPE_L2
}gd32_timer_type_enum;

typedef struct gd32_hwtimer{
    rt_hwtimer_t tim;
    rcu_periph_enum clk;
    uint32_t tim_periph;
    char *name;
    gd32_timer_type_enum type;
    IRQn_Type irq;
}gd32_hwtimer_t;

#endif /* DRIVERS_DRV_HWTIMER_H_ */
