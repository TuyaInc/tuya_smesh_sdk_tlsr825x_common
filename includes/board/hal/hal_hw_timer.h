/*************************************************************************
	> File Name: phy_tlsr825x_hw_timer.h
	> Author: jiangjj
	> Mail: 
	> Created Time: Fri 26 jul 2019 10:26:19 CST
 ************************************************************************/
#ifndef _HAL_HW_TIMER_H
#define _HAL_HW_TIMER_H

#include "hal_sys.h"


#ifdef TLSR825X_SYS

enum timer_src_num
{
	HAL_TIMER_0 = 0,
	HAL_TIMER_1 = 1,
	HAL_TIMER_2 = 2,
};

typedef int (*hal_hw_timer_callback_t)(void);


int hal_hw_timer_cfg(u32 timerId, u32 interval_us, hal_hw_timer_callback_t func);
int hal_imer_stop(u32 timerId);

void hal_hw_timer_handler();

#endif 

#endif
