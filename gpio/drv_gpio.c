/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-05     liuxin       the first version
 */
#include "drv_gpio.h"

static const pin_ pins[] = {
#ifdef GPIOA
    GD32_PIN(0, A, 0),
    GD32_PIN(1, A, 1),
    GD32_PIN(2, A, 2),
    GD32_PIN(3, A, 3),
    GD32_PIN(4, A, 4),
    GD32_PIN(5, A, 5),
    GD32_PIN(6, A, 6),
    GD32_PIN(7, A, 7),
    GD32_PIN(8, A, 8),
    GD32_PIN(9, A, 9),
    GD32_PIN(10, A, 10),
    GD32_PIN(11, A, 11),
    GD32_PIN(12, A, 12),
    GD32_PIN(13, A, 13),
    GD32_PIN(14, A, 14),
    GD32_PIN(15, A, 15),
#endif
#ifdef GPIOB
    GD32_PIN(16, B, 0),
    GD32_PIN(17, B, 1),
    GD32_PIN(18, B, 2),
    GD32_PIN(19, B, 3),
    GD32_PIN(20, B, 4),
    GD32_PIN(21, B, 5),
    GD32_PIN(22, B, 6),
    GD32_PIN(23, B, 7),
    GD32_PIN(24, B, 8),
    GD32_PIN(25, B, 9),
    GD32_PIN(26, B, 10),
    GD32_PIN(27, B, 11),
    GD32_PIN(28, B, 12),
    GD32_PIN(29, B, 13),
    GD32_PIN(30, B, 14),
    GD32_PIN(31, B, 15),
#endif
#ifdef GPIOC
    GD32_PIN(32, C, 0),
    GD32_PIN(33, C, 1),
    GD32_PIN(34, C, 2),
    GD32_PIN(35, C, 3),
    GD32_PIN(36, C, 4),
    GD32_PIN(37, C, 5),
    GD32_PIN(38, C, 6),
    GD32_PIN(39, C, 7),
    GD32_PIN(40, C, 8),
    GD32_PIN(41, C, 9),
    GD32_PIN(42, C, 10),
    GD32_PIN(43, C, 11),
    GD32_PIN(44, C, 12),
    GD32_PIN(45, C, 13),
    GD32_PIN(46, C, 14),
    GD32_PIN(47, C, 15),
#endif
#ifdef GPIOD
    GD32_PIN(48, D, 0),
    GD32_PIN(49, D, 1),
    GD32_PIN(50, D, 2),
    GD32_PIN(51, D, 3),
    GD32_PIN(52, D, 4),
    GD32_PIN(53, D, 5),
    GD32_PIN(54, D, 6),
    GD32_PIN(55, D, 7),
    GD32_PIN(56, D, 8),
    GD32_PIN(57, D, 9),
    GD32_PIN(58, D, 10),
    GD32_PIN(59, D, 11),
    GD32_PIN(60, D, 12),
    GD32_PIN(61, D, 13),
    GD32_PIN(62, D, 14),
    GD32_PIN(63, D, 15),
#endif
#ifdef GPIOE
    GD32_PIN(64, E, 0),
    GD32_PIN(65, E, 1),
    GD32_PIN(66, E, 2),
    GD32_PIN(67, E, 3),
    GD32_PIN(68, E, 4),
    GD32_PIN(69, E, 5),
    GD32_PIN(70, E, 6),
    GD32_PIN(71, E, 7),
    GD32_PIN(72, E, 8),
    GD32_PIN(73, E, 9),
    GD32_PIN(74, E, 10),
    GD32_PIN(75, E, 11),
    GD32_PIN(76, E, 12),
    GD32_PIN(77, E, 13),
    GD32_PIN(78, E, 14),
    GD32_PIN(79, E, 15),
#endif
#ifdef GPIOF
    GD32_PIN(80, F, 0),
    GD32_PIN(81, F, 1),
    GD32_PIN(82, F, 2),
    GD32_PIN(83, F, 3),
    GD32_PIN(84, F, 4),
    GD32_PIN(85, F, 5),
    GD32_PIN(86, F, 6),
    GD32_PIN(87, F, 7),
    GD32_PIN(88, F, 8),
    GD32_PIN(89, F, 9),
    GD32_PIN(90, F, 10),
    GD32_PIN(91, F, 11),
    GD32_PIN(92, F, 12),
    GD32_PIN(93, F, 13),
    GD32_PIN(94, F, 14),
    GD32_PIN(95, F, 15),
#endif
#ifdef GPIOG
    GD32_PIN(96, G, 0),
    GD32_PIN(97, G, 1),
    GD32_PIN(98, G, 2),
    GD32_PIN(99, G, 3),
    GD32_PIN(100, G, 4),
    GD32_PIN(101, G, 5),
    GD32_PIN(102, G, 6),
    GD32_PIN(103, G, 7),
    GD32_PIN(104, G, 8),
    GD32_PIN(105, G, 9),
    GD32_PIN(106, G, 10),
    GD32_PIN(107, G, 11),
    GD32_PIN(108, G, 12),
    GD32_PIN(109, G, 13),
    GD32_PIN(110, G, 14),
    GD32_PIN(111, G, 15),
#endif
#ifdef GPIOH
    GD32_PIN(112, H, 0),
    GD32_PIN(113, H, 1),
    GD32_PIN(114, H, 2),
    GD32_PIN(115, H, 3),
    GD32_PIN(116, H, 4),
    GD32_PIN(117, H, 5),
    GD32_PIN(118, H, 6),
    GD32_PIN(119, H, 7),
    GD32_PIN(120, H, 8),
    GD32_PIN(121, H, 9),
    GD32_PIN(122, H, 10),
    GD32_PIN(123, H, 11),
    GD32_PIN(124, H, 12),
    GD32_PIN(125, H, 13),
    GD32_PIN(126, H, 14),
    GD32_PIN(127, H, 15),
#endif
#ifdef GPIOI
    GD32_PIN(128, I, 0),
    GD32_PIN(129, I, 1),
    GD32_PIN(130, I, 2),
    GD32_PIN(131, I, 3),
    GD32_PIN(132, I, 4),
    GD32_PIN(133, I, 5),
    GD32_PIN(134, I, 6),
    GD32_PIN(135, I, 7),
    GD32_PIN(136, I, 8),
    GD32_PIN(137, I, 9),
    GD32_PIN(138, I, 10),
    GD32_PIN(139, I, 11),
    GD32_PIN(140, I, 12),
    GD32_PIN(141, I, 13),
    GD32_PIN(142, I, 14),
    GD32_PIN(143, I, 15),
#endif
};

static struct rt_pin_irq_hdr tab[] = {
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL}};

static const pin_irq_map pin_interrupt_handler[] =
    {
        {GPIO_PIN_0, EXTI0_IRQn},
        {GPIO_PIN_1, EXTI1_IRQn},
        {GPIO_PIN_2, EXTI2_IRQn},
        {GPIO_PIN_3, EXTI3_IRQn},
        {GPIO_PIN_4, EXTI4_IRQn},
        {GPIO_PIN_5, EXTI5_9_IRQn},
        {GPIO_PIN_6, EXTI5_9_IRQn},
        {GPIO_PIN_7, EXTI5_9_IRQn},
        {GPIO_PIN_8, EXTI5_9_IRQn},
        {GPIO_PIN_9, EXTI5_9_IRQn},
        {GPIO_PIN_10, EXTI10_15_IRQn},
        {GPIO_PIN_11, EXTI10_15_IRQn},
        {GPIO_PIN_12, EXTI10_15_IRQn},
        {GPIO_PIN_13, EXTI10_15_IRQn},
        {GPIO_PIN_14, EXTI10_15_IRQn},
        {GPIO_PIN_15, EXTI10_15_IRQn},
};

/**
 * @brief  bit2bitno
 * @param  bit
 * @retval None
 */
rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    rt_uint8_t i;
    for (i = 0; i < 32; i++)
    {
        if ((0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}

static const
#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
    pin_ *
    pin_get(rt_base_t index)
{

    if (index < ITEM_NUM(pins))
    {
        return &pins[index];
    }
    else
    {
        RT_ASSERT(index < ITEM_NUM(pins));
        return RT_NULL;
    }
}

void pin_mode(struct rt_device *device, rt_base_t pin, rt_base_t m)
{
    const pin_ *index = pin_get(pin);
    rt_uint32_t mode, pupd = GPIO_PUPD_NONE, otype;
    switch (m)
    {
    case PIN_MODE_OUTPUT:
        mode = GPIO_MODE_OUTPUT;
        otype = GPIO_OTYPE_PP;
        break;
    case PIN_MODE_OUTPUT_OD:
        mode = GPIO_MODE_OUTPUT;
        otype = GPIO_OTYPE_OD;
        break;
    case PIN_MODE_INPUT:
        mode = GPIO_MODE_INPUT;
        pupd = GPIO_PUPD_NONE;
        break;
    case PIN_MODE_INPUT_PULLUP:
        mode = GPIO_MODE_INPUT;
        pupd = GPIO_PUPD_PULLUP;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        mode = GPIO_MODE_INPUT;
        pupd = GPIO_PUPD_PULLDOWN;
        break;
    }
    rcu_periph_clock_enable(index->clk);
    gpio_mode_set(index->gpio_periph, mode, pupd, index->pin);
    if (mode == GPIO_MODE_OUTPUT)
    {
        gpio_output_options_set(index->gpio_periph, otype, GPIO_OSPEED_50MHZ, index->pin);
    }
}

void pin_write(struct rt_device *device, rt_base_t pin, rt_base_t value)
{
    const pin_ *index = pin_get(pin);
    gpio_bit_write(index->gpio_periph, index->pin, (bit_status)value);
}

int pin_read(struct rt_device *device, rt_base_t pin)
{
    const pin_ *index = pin_get(pin);
    return gpio_input_bit_get(index->gpio_periph, index->pin);
}
//"PA.5"
rt_base_t pin_get_index(const char *name)
{
    uint8_t a = name[1] - 'A';
    uint8_t pin = atoi(&name[3]);
    return a * 16 + pin;
}

rt_err_t pin_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level = rt_hw_interrupt_disable();
    const pin_ *index = &pins[pin];
    uint8_t i = bit2bitno(index->pin);
    tab[i].pin = pin;
    tab[i].mode = mode;
    tab[i].hdr = hdr;
    tab[i].args = args;
    rt_hw_interrupt_enable(level);
    rt_kprintf("attach mode %d\n", tab[i].mode);
    return RT_EOK;
}

rt_err_t pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{

    uint8_t level = rt_hw_interrupt_disable();
    const pin_ *index = &pins[pin];
    uint8_t i = bit2bitno(index->pin);
    if (enabled == PIN_IRQ_ENABLE)
    {
        uint32_t irq_mode = tab[i].mode;
        rt_kprintf("enable mode %d %d\n", i, irq_mode);
        switch (irq_mode)
        {
        case PIN_IRQ_MODE_FALLING:
            irq_mode = EXTI_TRIG_FALLING;
            break;
        case PIN_IRQ_MODE_RISING:
            irq_mode = EXTI_TRIG_RISING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            irq_mode = EXTI_TRIG_BOTH;
            break;
        default:
            return RT_ERROR;
        }
        rcu_periph_clock_enable(RCU_SYSCFG);
        uint8_t i = bit2bitno(index->pin);
        nvic_irq_enable(pin_interrupt_handler[i].type, 0, 0);

        syscfg_exti_line_config(index->port_src, index->pin_src);

        exti_init((exti_line_enum)(index->pin), EXTI_INTERRUPT, (exti_trig_type_enum)irq_mode);
        exti_interrupt_flag_clear((exti_line_enum)(index->pin));
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        nvic_irq_disable(pin_interrupt_handler[i].type);
    }
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

rt_err_t pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    uint8_t level = rt_hw_interrupt_disable();
    const pin_ *index = &pins[pin];
    uint8_t i = bit2bitno(index->pin);
    tab[i].pin = -1;
    tab[i].mode = RT_NULL;
    tab[i].hdr = RT_NULL;
    tab[i].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

const struct rt_pin_ops gpio_ops = {pin_mode, pin_write, pin_read, pin_attach_irq, pin_detach_irq, pin_irq_enable, pin_get_index};

void rt_hw_gpio_init(void)
{
    rt_device_pin_register("pin", &gpio_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_gpio_init);

void GD32_GPIO_EXTI_IRQHandler(uint8_t index)
{
    tab[index].hdr(tab[index].args);
    exti_interrupt_flag_clear((exti_line_enum)1 << index);
}

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(0);
    rt_interrupt_leave();
}

void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(1);
    rt_interrupt_leave();
}

void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(2);
    rt_interrupt_leave();
}

void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(3);
    rt_interrupt_leave();
}

void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(4);
    rt_interrupt_leave();
}

void EXTI5_9_IRQHandler(void)
{
    rt_interrupt_enter();
    for (uint8_t i = 5; i <= 9; i++)
    {
        if (exti_interrupt_flag_get((exti_line_enum)1 << i))
        {
            GD32_GPIO_EXTI_IRQHandler(i);
        }
    }
    rt_interrupt_leave();
}

void EXTI10_15_IRQHandler(void)
{
    rt_interrupt_enter();
    for (uint8_t i = 10; i <= 15; i++)
    {
        if (exti_interrupt_flag_get((exti_line_enum)1 << i))
        {
            GD32_GPIO_EXTI_IRQHandler(i);
        }
    }
    rt_interrupt_leave();
}
