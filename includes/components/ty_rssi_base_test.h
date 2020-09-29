/*************************************************************************
	> File Name: ty_rssi_base_test.h
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Mar 2019 14:58:14 CST
 ************************************************************************/

#ifndef _TY_RSSI_BASE_TEST_H
#define _TY_RSSI_BASE_TEST_H

#include "board.h"

typedef void (*CallBackS)(void);

// 注册start和stop回调函数，方便应用层逻辑在此时做应用层处理
extern void ty_rssi_base_test_register_start_stop_cb(CallBackS start_cb,CallBackS stop_cb);

extern void ty_rssi_base_test_start(void);
extern void ty_rssi_base_test_stop(void);
extern void ty_rssi_base_test_update_rssi(u8 rssi);
extern s8 ty_rssi_base_test_get_rssi_avg(int *rssi);


#endif
