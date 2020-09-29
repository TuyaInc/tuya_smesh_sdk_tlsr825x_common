/*************************************************************************
	> File Name: hal_sleep.h
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2019 21:17:50 CST
 ************************************************************************/

#ifndef _HAL_SLEEP_H
#define _HAL_SLEEP_H

#include "hal_sys.h"


typedef enum{
    hal_Level_Low=0,
    hal_Level_High =1,
}hal_GPIO_Level_t;

typedef enum {
    //available mode for customer
    HAL_SUSPEND_MODE						= 0,

    HAL_DEEPSLEEP_MODE						= 0x80,
    HAL_DEEPSLEEP_MODE_RET_SRAM_LOW16K  	= 0x43,  //for boot from sram
    HAL_DEEPSLEEP_MODE_RET_SRAM_LOW32K  	= 0x07,  //for boot from sram

    //not available mode
    HAL_DEEPSLEEP_RETENTION_FLAG			= 0x7F,
}hal_SleepMode_t;

typedef enum {
    //available wake-up source for customer
    HAL_PM_WAKEUP_PAD   = BIT(4), HAL_SUSPENDWAKEUP_SRC_PAD  = BIT(4), HAL_DEEPWAKEUP_SRC_PAD   = BIT(4),
    HAL_PM_WAKEUP_CORE  = BIT(5),	
    HAL_PM_WAKEUP_TIMER = BIT(6), HAL_SUSPENDWAKEUP_SRC_TIMER= BIT(6), HAL_DEEPWAKEUP_SRC_TIMER = BIT(6),
    //not available wake-up source for customer
    HAL_PM_TIM_RECOVER_START   = BIT(14),
    HAL_PM_TIM_RECOVER_END     = BIT(15),
}hal_wakeup_set_t;


typedef enum {
    HAL_WAKEUP_FROM_POWER = 0x00,
    HAL_WAKEUP_FROM_TIMER,
    HAL_WAKEUP_FROM_PIN_PAD,
}hal_wakeup_src_t;

hal_wakeup_src_t hal_get_wakeup_src(void);
int hal_cpu_sleep_wakeup(hal_SleepMode_t deepsleep, hal_wakeup_set_t wakeup_src, u32 wakeup_tick);
void hal_gpio_set_wakeup(u32 pin, hal_GPIO_Level_t level, int en);


#endif
