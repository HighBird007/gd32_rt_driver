#include "drv_iwd.h"


// 1s
// value in 0x0000 - 0x0FFF
#define WATCH_DOG_RELOAD_DEFAULT 128
#define WATCH_DOG_PRESCALER_DEFAULT FWDGT_PSC_DIV256

static rt_err_t init_iwdg(rt_watchdog_t *wdt)
{
	rt_uint16_t timeout = 0xFFFFU;
	rcu_osci_on(RCU_IRC32K);
	while (rcu_osci_stab_wait(RCU_IRC32K) != SUCCESS && timeout > 0)
	{
		timeout--;
	}
	fwdgt_write_enable();
	fwdgt_config(WATCH_DOG_RELOAD_DEFAULT, WATCH_DOG_PRESCALER_DEFAULT);
	fwdgt_write_disable();
}
static rt_err_t control_iwdg(rt_watchdog_t *wdt, int cmd, void *arg)
{
	rt_uint32_t time = *(rt_uint32_t *)arg;
	switch (cmd)
	{
	case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
		return RT_ERROR;
	case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
		fwdgt_write_enable();
		fwdgt_config(WATCH_DOG_RELOAD_DEFAULT * time, WATCH_DOG_PRESCALER_DEFAULT);
		fwdgt_write_disable();
		break;
	case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
		return RT_ERROR;
	case RT_DEVICE_CTRL_WDT_KEEPALIVE:
		fwdgt_counter_reload();
		break;
	case RT_DEVICE_CTRL_WDT_START:
		fwdgt_enable();
		break;
	case RT_DEVICE_CTRL_WDT_STOP:
		return RT_ERROR;
	}
	return RT_EOK;
}
static struct rt_watchdog_ops __ops = {init_iwdg, control_iwdg};
static struct rt_watchdog_device w;
static void init(void)
{
	w.ops = &__ops;
	if (rt_hw_watchdog_register(&w, WATCH_DOG_NAME, RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
	{
		rt_kprintf("watch dog error \n");
	}
}
INIT_BOARD_EXPORT(init);
