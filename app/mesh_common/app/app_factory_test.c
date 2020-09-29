/*************************************************************************
	> File Name: app_factory_test.c
	> Author: 
	> Mail: 
	> Created Time: Wed 12 Aug 2020 11:57:09 CST
 ************************************************************************/
#include "ty_uart_cmd_server_for_factory_test.h"
#include "ty_gpio_base_test.h"
#include "base_oem_config.h"

static u8 if_enter_factory_test = 0;
ty_uart_cmd_server_for_factory_test_params_s ty_uart_cmd_server_for_factory_test_params = {
    .is_need_fingerprint_check = 1,
    .is_need_get_pid_from_cloud = 0,
    .if_support_country_code = 0,
    .if_support_gpio_test_num = 1,

    .is_need_update_mac_in_flash = 1,
    .mac_address = 0x76000, 

    .firmname = BUILD_FIRMNAME,
    .firmversion = FW_VERSION,
};
void factory_test_enter_cb(void){
    PR_DEBUG("ENTER\n");   
    if_enter_factory_test = 1;
}
u8 factory_test_rssi_test_cb(void){
    int rssi = 0;
    ty_rssi_base_test_stop();
    if(ty_rssi_base_test_get_rssi_avg(&rssi) != -1){
       if(rssi > 0 && rssi < 75){
            return rssi;
       }  
    }
    return 0;
}
void factory_test_reset_cb(void){

}

//------------------------------------------------------------------------
void app_factory_test_init(void){
    ty_uart_cmd_server_for_factory_test.init(&ty_uart_cmd_server_for_factory_test_params);
    ty_uart_cmd_server_for_factory_test.set_enter_callback(&factory_test_enter_cb);
    ty_uart_cmd_server_for_factory_test.set_gpio_test_callback(&ty_gpio_base_test_auto);
    ty_uart_cmd_server_for_factory_test.set_rssi_test_callback(&factory_test_rssi_test_cb);
    ty_uart_cmd_server_for_factory_test.set_reset_callback(&factory_test_reset_cb);
}

int app_factory_test_cmd(u8 cmd, u8 *data, u8 len){
    ty_uart_cmd_server_for_factory_test.receive_cmd(cmd,data,len);
}

int app_factory_test_run(void){
    
}

int app_factory_test_if_enter(void){
    return if_enter_factory_test;
}
