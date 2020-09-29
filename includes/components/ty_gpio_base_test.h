/*************************************************************************
	> File Name: ty_gpio_base_test.h
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Mar 2019 15:11:13 CST
 ************************************************************************/

#ifndef _TY_GPIO_BASE_TEST_H
#define _TY_GPIO_BASE_TEST_H

#include "board.h"


#define MAX_GPIO_TEST_PIN           10
#define MAX_GPIO_TEST_PIN_MORE      (MAX_GPIO_TEST_PIN + 1)   //=8+1

#define ARRAY_SIZE(a) 			(sizeof(a) / sizeof(*a))


typedef struct{
    u8 pin_num;
    u32 pin[MAX_GPIO_TEST_PIN];
    u8 map[MAX_GPIO_TEST_PIN];
    u8 ret[MAX_GPIO_TEST_PIN_MORE];
}ty_gpio_base_test_s;

typedef struct{
    u8 num;
    u32 pin;
}num2pin_t;


extern u8 ty_gpio_base_test_auto(u8 *para, u8 len);


#endif
