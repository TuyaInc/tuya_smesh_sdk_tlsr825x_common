/*************************************************************************
	> File Name: hal_gpio.h
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Apr 2019 21:17:50 CST
 ************************************************************************/

#ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

#include "hal_sys.h"
#include "gpio_8258.h"

typedef int (*hal_gpio_irq_callback_t)(void);

//gpio InOut choice
typedef enum{
    GPIO_MODE_INPUT = 0x00,
    GPIO_MODE_OUTPUT,
}hal_gpio_in_out_mode_e;


//gpio function choice
typedef enum{
    GPIO_FUNC_AS_NOT_GPIO = 0x00,
    GPIO_FUNC_AS_GPIO,
    GPIO_FUNC_AS_UART,
    GPIO_FUNC_AS_PWM,
    GPIO_FUNC_AS_I2C,
    GPIO_FUNC_AS_SPI,
    GPIO_FUNC_AS_ADC,
}hal_gpio_func_e;

//gpio up down resistor level
typedef enum{
    GPIO_RESISTOR_FLOAT = 0x00,
    GPIO_RESISTOR_PULLUP_1M,
    GPIO_RESISTOR_PULLUP_10K,
    GPIO_RESISTOR_PULLDOWN_100K,
}hal_gpio_up_down_resistor_level_e;

typedef enum{
    HAL_FLD_IRQ_GPIO_EN =			BIT(18),
    HAL_FLD_IRQ_GPIO_RISC0_EN =		BIT(21),
    HAL_FLD_IRQ_GPIO_RISC1_EN =		BIT(22),
}HAL_FLD_IRQ_EN;


//GPIO DEFINE
#define GPIO_PA0 GPIO_PA0 
#define GPIO_PA1 GPIO_PA1 
#define GPIO_PA2 GPIO_PA2
#define GPIO_PA3 GPIO_PA3
#define GPIO_PA4 GPIO_PA4
#define GPIO_PA5 GPIO_PA5
#define GPIO_PA6 GPIO_PA6
#define GPIO_PA7 GPIO_PA7
#define GPIO_PB0 GPIO_PB0
#define GPIO_PB1 GPIO_PB1
#define GPIO_PB2 GPIO_PB2
#define GPIO_PB3 GPIO_PB3
#define GPIO_PB4 GPIO_PB4
#define GPIO_PB5 GPIO_PB5
#define GPIO_PB6 GPIO_PB6
#define GPIO_PB7 GPIO_PB7
#define GPIO_PC0 GPIO_PC0
#define GPIO_PC1 GPIO_PC1
#define GPIO_PC2 GPIO_PC2
#define GPIO_PC3 GPIO_PC3
#define GPIO_PC4 GPIO_PC4
#define GPIO_PC5 GPIO_PC5
#define GPIO_PC6 GPIO_PC6
#define GPIO_PC7 GPIO_PC7
#define GPIO_PD0 GPIO_PD0
#define GPIO_PD1 GPIO_PD1
#define GPIO_PD2 GPIO_PD2
#define GPIO_PD3 GPIO_PD3
#define GPIO_PD4 GPIO_PD4
#define GPIO_PD5 GPIO_PD5
#define GPIO_PD6 GPIO_PD6
#define GPIO_PD7 GPIO_PD7
#define GPIO_PE0 GPIO_PE0
#define GPIO_PE1 GPIO_PE1
#define GPIO_PE2 GPIO_PE2
#define GPIO_PE3 GPIO_PE3
#define GPIO_PE4 
#define GPIO_PE5 
#define GPIO_PE6 
#define GPIO_PE7 


// special: set the gpio some function
extern void hal_gpio_set_func(u32 pin, hal_gpio_func_e func);

// judge if input or output
extern int hal_gpio_is_output_en(u32 pin);
extern int hal_gpio_is_input_en(u32 pin);

// set input or output
extern void hal_gpio_set_output_en(u32 pin, u32 value);//0-disable  1-enable
extern void hal_gpio_set_input_en(u32 pin, u32 value);//0-disable  1-enable
extern void hal_gpio_setup_up_down_resistor(u32 pin, hal_gpio_up_down_resistor_level_e level);

// read & write
extern void hal_gpio_write(u32 pin ,u32 value);//0-low 1-high
extern void hal_gpio_toggle(u32 pin);
extern u32 hal_gpio_read(u32 pin);//0 !0

/********************************************************
*
*	@brief		gpio_set_interrupt_init
*
*	@param		pin - gpio.
*				up_down - PM_PIN_PULLUP_10K; PM_PIN_PULLDOWN_100K.
*				falling - 0:rising edge; 1:falling edge.
*				irq_mask - set interrupt mask:FLD_IRQ_GPIO_EN,FLD_IRQ_GPIO_RISC0_EN,FLD_IRQ_GPIO_RISC1_EN,	FLD_IRQ_GPIO_RISC2_EN 
*	@return		None
*/

void hal_gpio_set_interrupt_init(u32 pin, hal_gpio_up_down_resistor_level_e up_down, u32 falling, HAL_FLD_IRQ_EN irq_mask, hal_gpio_irq_callback_t func);

#endif
