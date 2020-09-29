/*************************************************************************
	> File Name: app_rssi.c
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Mar 2019 14:52:02 CST
 ************************************************************************/
#include "app_rssi.h"
#include "ty_string_op.h"
#include "ty_nv.h"
#include "ty_rssi_base_test.h"
#include "tuya_sigmesh_hal.h"
#include "hal_log.h"
#include "ty_uart_cmd_server_for_factory_test.h"
#include "ty_timer_event.h"


extern AppVendorS mAppVendor; 

static u8 is_rssi_test = 0;

void rssi_test_start_cb(void){
    tuya_ble_hal_gatt_scan(1);
    is_rssi_test = 1;
}

void rssi_test_stop_cb(void){
    tuya_ble_hal_gatt_scan(0);
    is_rssi_test = 0;
}

int mf_test_get_rssi_callback(void){
    int rssi = 0;
    ty_rssi_base_test_stop();

    if(ty_rssi_base_test_get_rssi_avg(&rssi) != -1){
        APP_LOG("!!!mf_test_rssi:%d\r\n",rssi);
        if(rssi > 0 && rssi < 90){

            s8 Prod_rssi = 0;
            Prod_rssi = ~((s8)rssi) + 1;
            u8 auth_state = is_auth_by_tuya();
            tuya_mdev_test(auth_state, Prod_rssi);
        }
    }

    return -1;
}

void app_rssi_init(void){
    if(get_if_factory_test_close()){
        APP_LOG("factory_test_close\r\n");
        return;
    }

    if(get_if_prov_success()){
        return;
    }

    is_rssi_test = 0;
    /*
     * 将rssi测试时开始和停止的回调注册
     * 在开始的时候关闭sig mesh广播包过滤策略
     * 在停止后打开过滤策略
     * 因为sig mesh虽然能够搜索蓝牙广播包，但是会过滤掉具备连接属性的广播包来节省搜索开销
     */
    ty_rssi_base_test_register_start_stop_cb(rssi_test_start_cb,rssi_test_stop_cb);

    ty_rssi_base_test_start();
    ty_timer_event_add(mf_test_get_rssi_callback , 1300*1000);
}

void app_rssi_run(u8 *adv, u8 adv_len, u8 *mac, int rssi){
    if(is_rssi_test == 1){
        ty_string_op_data_s adv_info,name_info;
        adv_info.len = adv_len;
        adv_info.data = adv;

        if(0 == ty_string_op_adv_report_parse(0x09,&adv_info,&name_info)){
            if(name_info.len == 7 && memcmp(name_info.data,"ty_prod",7) == 0){
                if(0 == get_if_uart_init()){
                    app_uart_init();
                }
                ty_rssi_base_test_update_rssi(rssi);
            }else if(name_info.len == 7 && memcmp(name_info.data,"ty_mdev",7) == 0){
                ty_rssi_base_test_update_rssi(rssi);
            }
        }
    }
}

