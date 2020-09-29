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

void mesh_oem_config_init(void ){
#if JSON_CONFIG_ON
    APP_LOG("%s\r\n",__FUNCTION__);
    u8 buf[256];
    u16 len = 0;

    tuya_oem_config_load(&len, buf);
#endif
}

void mesh_app_init(void){
    APP_LOG("%s\r\n",__FUNCTION__);
}

void mesh_main_run(void){
    
}

void mesh_factory_reset(void){
    APP_LOG("%s\r\n",__FUNCTION__);
//    nv_resetAll();
}

void tuya_mdev_test(uint8_t is_Authorized, uint8_t rssi){
    APP_LOG("%s\r\n",__FUNCTION__);
    tuya_gatt_adv_beacon_enable(0); // when mdev test close prov, if do not need can delete this callback
    
}

void mesh_state_callback(mesh_state_t stat){
    APP_LOG("%s :%d\r\n", __FUNCTION__, stat);
    
}

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





