/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-05     liuxin       the first version
 */
#ifndef DRIVERS_DRV_GPIO_H_
#define DRIVERS_DRV_GPIO_H_
#include <rtthread.h>
#include "gd32f4xx.h"
#include "rtdevice.h"


#define GD32_PIN(index, port, pin) {index, RCU_GPIO##port,      \
                                    GPIO##port, GPIO_PIN_##pin, \
                                    EXTI_SOURCE_GPIO##port,     \
                                    EXTI_SOURCE_PIN##pin}

typedef struct{
    rt_uint8_t index;
    rcu_periph_enum clk;
    uint32_t gpio_periph;
    uint32_t pin;
    rt_uint8_t port_src;
    rt_uint8_t pin_src;
}pin_;

typedef struct{
    uint32_t pin;
    IRQn_Type type;
}pin_irq_map;

#endif /* DRIVERS_DRV_GPIO_H_ */
