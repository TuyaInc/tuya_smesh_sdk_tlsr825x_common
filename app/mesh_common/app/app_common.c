/*************************************************************************
	> File Name: app_common.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Feb 2019 22:29:34 CST
 ************************************************************************/

#include "app_common.h"
#include "hal_log.h"
#include "tuya_sigmesh_hal.h"
#include "base_oem_config.h"
#include "ty_uart_cmd_server_for_sig_mesh_uart_common.h"

/**
* @description: when mdev restarts,sending a heartbeat packet. 
* @param[in] none
* @param[in] none
* @return none
*/
void restart_send_heart(void){
    if((get_if_prov_success()) && (ty_uart_cmd_server_for_sig_mesh_uart_common.get_is_low_power_model() == 0)){//online and not low power model 
        u8 para[1];
        para[0] = 0x01;
        u8 src_addr = get_primary_ele_addr();        
        tuya_mesh_data_send(src_addr, 0xD000, TUYA_G_ONOFF_STATUS, para, 1, 0, 0);//send to gateway and phone
    }
}


void mesh_oem_config_init(void ){
#if JSON_CONFIG_ON
    APP_LOG("%s\r\n",__FUNCTION__);
    u8 buf[256];
    u16 len = 0;

    tuya_oem_config_load(&len, buf);
#endif
}

void mesh_app_init(void){//用于应用层逻辑的初始化
    APP_LOG("%s\r\n",__FUNCTION__);
    restart_send_heart();
}

void mesh_main_run(void){//用于应用层逻辑的周期性执行   
}

void mesh_factory_reset(void){//设备被重置前会调用该函数，用于应用层在设备重置时清空一些应用层级别的 flash 数据
    APP_LOG("%s\r\n",__FUNCTION__);
//    nv_resetAll();
}

void tuya_mdev_test(uint8_t is_Authorized, uint8_t rssi){//烧录授权时的产测回调函数，一般不要改，不要动
    APP_LOG("%s\r\n",__FUNCTION__);
    tuya_gatt_adv_beacon_enable(0); // when mdev test close prov, if do not need can delete this callback
    
}

void mesh_state_callback(mesh_state_t stat){//各种mesh状态发生变化时，会调用该函数，通知给应用层（看 mesh_state_t 可知道有哪些信息会上报）
    switch(stat){
        case TY_GROUP_SUB_ADD:
        case TY_GROUP_SUB_DEL:
            app_mcu_protocol_report_group_address();
            break;
        default:
            break;
    }
    APP_LOG("%s :%d\r\n", __FUNCTION__, stat);
    
}
//手机 -> 设备的数据回调函数（非常重要）
/*
src_addr[in]：数据源地址
dst_addr[in]：数据目的地址
opcode[in]：命令字
data[in]：数据指针
data_len[in]：数据长度
ttl[in]：数据剩余转发次数
*/
void tuya_mesh_data_recv_callback(uint16_t src_addr, uint16_t dst_addr, uint32_t opcode, uint8_t *data, uint16_t data_len, uint8_t ttl)
{
    if(get_primary_ele_addr() == src_addr){
        return;
    }

    switch(opcode){
        case TUYA_G_ONOFF_GET:{
            u8 para[1];
            para[0] = 0x01;
            tuya_mesh_data_send(dst_addr, src_addr, TUYA_G_ONOFF_STATUS, para, 1, 0, 1);
            }
            break;
  // vendor model cmd-----------------
        case TUYA_VD_TUYA_WTITE:
        case TUYA_VD_TUYA_WRITE_NOACK:
            app_mesh_vendor_write(src_addr,dst_addr,data,data_len,0); 
        break;

        case TUYA_VD_TUYA_READ:{
            app_mesh_vendor_read(src_addr,dst_addr,data,data_len,0);
        }
        break;
	}
}








