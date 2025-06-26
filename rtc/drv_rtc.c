/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-25     liuxin       the first version
 */
#include "drv_rtc.h"
#include "time.h"
#define RTC_NAME    "rtc"
#define BKP_VALUE    0x32F1

// 十位取出左移4位 + 个位 (得到BCD数)
#define WRITE_BCD(val)     ((val / 10) << 4) + (val % 10)
// 将高4位乘以10 + 低四位 (得到10进制数)
#define READ_BCD(val)     (val >> 4) * 10 + (val & 0x0F)

static rt_rtc_dev_t rtc;

/**
 *     rt_err_t (*init)(void);
    rt_err_t (*get_secs)(void *arg);
    rt_err_t (*set_secs)(void *arg);
    rt_err_t (*get_alarm)(void *arg);
    rt_err_t (*set_alarm)(void *arg);
    rt_err_t (*get_timeval)(void *arg);
    rt_err_t (*set_timeval)(void *arg);
 */
static rt_err_t gd32_rtc_init(void){
    rcu_periph_clock_enable(RCU_PMU);
    pmu_backup_write_enable();

    rcu_osci_on(RCU_IRC32K);
    rcu_osci_stab_wait(RCU_IRC32K);
    rcu_rtc_clock_config(RCU_RTCSRC_IRC32K);

    rcu_periph_clock_enable(RCU_RTC);
    rtc_register_sync_wait();

    if(BKP_VALUE == RTC_BKP0)return RT_EOK;
    RTC_BKP0 = BKP_VALUE;
    return RT_EOK;
}

rt_err_t gd32_rtc_get_secs(void *arg)
{
    struct tm t = {0};
    rtc_parameter_struct rtc_param;
    time_t *timestamp = (time_t *)arg;

    // 获取当前时间参数
    rtc_current_time_get(&rtc_param);
    // 从 BCD 转为十进制并填充 struct tm
    t.tm_year = READ_BCD(rtc_param.year) + 100; // tm_year = 年份 - 1900
    t.tm_mon  = READ_BCD(rtc_param.month) - 1;  // tm_mon = 0~11
    t.tm_mday = READ_BCD(rtc_param.date);
    t.tm_wday = rtc_param.day_of_week % 7;      // RTC 1=周一, tm 0=周日
    t.tm_hour = READ_BCD(rtc_param.hour);
    t.tm_min  = READ_BCD(rtc_param.minute);
    t.tm_sec  = READ_BCD(rtc_param.second);

    // 转为 time_t 时间戳
    *timestamp = mktime(&t);

    return RT_EOK;
}


rt_err_t gd32_rtc_set_secs(void *arg)
{
    time_t *timestamp = (time_t *)arg;
    struct tm t;
    rtc_parameter_struct rtc_param;

    // 将 time_t 转成 struct tm
    localtime_r(timestamp, &t);

    // 转换为 BCD 格式并赋值
    rtc_param.year = WRITE_BCD(t.tm_year % 100);      // 取后两位年份
    rtc_param.month = WRITE_BCD(t.tm_mon+1);        // 月份从0开始，+1
    rtc_param.date = WRITE_BCD(t.tm_mday);            // 日期
    rtc_param.day_of_week = t.tm_wday == 0 ? 7 : t.tm_wday; // 星期：tm_wday=0表示周日，RTC中1=周一，7=周日
    rtc_param.hour = WRITE_BCD(t.tm_hour);
    rtc_param.minute = WRITE_BCD(t.tm_min);
    rtc_param.second = WRITE_BCD(t.tm_sec);

    // 默认 32.768KHz 预分频（1Hz）
    rtc_param.factor_asyn = 0x7F;
    rtc_param.factor_syn  = 0xFF;
    //rtc_param.am_pm = RTC_AM;              // 24小时制
    rtc_param.display_format = RTC_24HOUR;

    rtc_init(&rtc_param);  // 初始化并设置时间

    return RT_EOK;
}

static struct rt_rtc_ops rtc_ops = {
        gd32_rtc_init,gd32_rtc_get_secs,gd32_rtc_set_secs
};

void gd32_hw_rtc_init(void){
    rtc.ops = &rtc_ops;
    rt_hw_rtc_register(&rtc,RTC_NAME,RT_DEVICE_FLAG_RDWR,NULL);
}
INIT_BOARD_EXPORT(gd32_hw_rtc_init);
