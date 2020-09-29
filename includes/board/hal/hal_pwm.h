/*************************************************************************
	> File Name: hal_pwm.h
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2019 21:17:50 CST
 ************************************************************************/

#ifndef _HAL_PWM_H
#define _HAL_PWM_H

#include "hal_sys.h"

#define hal_pwm_set(a, b, c)                pwm_set(a, b, c)
#define HAL_GET_PWMID(gpio, func)           GET_PWMID(gpio, func)
#define HAL_GET_PWM_INVERT_VAL(gpio, func)  GET_PWM_INVERT_VAL(gpio, func)

void hal_pwm_start(pwm_id id);
void hal_pwm_stop(pwm_id id);
void hal_pwm_revert(pwm_id id);
void hal_pwm_n_revert(pwm_id id);
void hal_pwm_set_cmp(pwm_id id, unsigned short cmp_tick);



#endif
