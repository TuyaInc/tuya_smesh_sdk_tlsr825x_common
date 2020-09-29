/*************************************************************************
	> File Name: hal_uart.h
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Jun 2018 08:32:09 PM CST
 ************************************************************************/

#ifndef _HAL_UART_H
#define _HAL_UART_H

#include "hal_sys.h"

typedef enum{
    BAUD_RATE_9600,
    BAUD_RATE_19200,
    BAUD_RATE_115200,
}BAUD_TYPE_t;

#define GPIO_UART0_TX GPIO_PB1
#define GPIO_UART0_RX GPIO_PB7
#define GPIO_UART1_TX GPIO_PB1   //for BT8C
#define GPIO_UART1_RX GPIO_PB0

extern int hal_uart_init(BAUD_TYPE_t baud_rate, u32 pin_tx, u32 pin_rx);
extern int hal_uart_send(u8 *datas, u8 length);
extern int hal_uart_read(u8 *datas, u8 length); 

#endif
