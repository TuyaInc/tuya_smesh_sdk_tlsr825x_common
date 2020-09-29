/*************************************************************************
	> File Name: app_rssi.h
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Mar 2019 14:52:08 CST
 ************************************************************************/

#ifndef _APP_RSSI_H
#define _APP_RSSI_H

#include "board.h"

extern void app_rssi_init(void);
extern void app_rssi_run(u8 *adv, u8 adv_len, u8 *mac, int rssi);



#endif
