/*************************************************************************
	> File Name: app_mcu_protocol.c
	> Author: 
	> Mail: 
	> Created Time: Wed 12 Aug 2020 15:31:31 CST
 ************************************************************************/
#include "ty_uart_cmd_server_for_sig_mesh_uart_common.h"
#include "tuya_sigmesh_hal.h"
#include "app_unprov_beacon.h"
#include "app_storage.h"


int app_mesh_vendor_write(u16 adr_src, u16 adr_dst, u8 *para, u8 len, u8 is_ack);
int app_mesh_vendor_read(u16 adr_src, u16 adr_dst, u8 *para, u8 len, u8 is_ack);
void app_mesh_vendor_ad_tx(u16 adr_src, u16 adr_dst, u8 *params, u8 len, u8 is_use_params_adr);

ty_uart_cmd_server_for_sig_mesh_uart_common_params_s ty_uart_cmd_server_for_sig_mesh_uart_common_params = {
};
u8 uart_common_query_info_cb(u8 *para, u8 len){
    if(len != 13)return 0;
    app_unprov_beacon_update_pid(para, 8);
    return 1;
}

u8 mcu_factory_test_rssi_test_cb(u8 is_start_or_stop){//asynchronous
    if(is_start_or_stop != 0){//start
        ty_rssi_base_test_start();
        return 1;
    }else{//stop
        int rssi = 0;
        ty_rssi_base_test_stop();
        if(ty_rssi_base_test_get_rssi_avg(&rssi) != -1){
            if(rssi > 0 && rssi < 75){
                return rssi;
            }  
        }
        return 0;
    }
}

//---------------------------------------------------------------
enum {
    KEY_OFFSET_LOW_POWER_FLAG = 0x00,
    KEY_OFFSET_MESH_LOCAL_CONTROL_MODE = 0x01,
    KEY_OFFSET_PUBADDRESS = 0x02,
};


void app_mcu_protocol_init(void){
    ty_uart_cmd_server_for_sig_mesh_uart_common.init(&ty_uart_cmd_server_for_sig_mesh_uart_common_params);
    ty_uart_cmd_server_for_sig_mesh_uart_common.set_work_state(0);
    ty_uart_cmd_server_for_sig_mesh_uart_common.set_work_mode(0);
    ty_uart_cmd_server_for_sig_mesh_uart_common.set_query_info_callback(&uart_common_query_info_cb);
    ty_uart_cmd_server_for_sig_mesh_uart_common.set_reset_callback(&tuya_mesh_network_reset);
    ty_uart_cmd_server_for_sig_mesh_uart_common.set_rssi_test_callback(&mcu_factory_test_rssi_test_cb);
    ty_uart_cmd_server_for_sig_mesh_uart_common.set_ad_tx_callback(&app_mesh_vendor_ad_tx);


    //读取存储在flash中的数据，如果有历史数据，则用历史数据，如果没有则用默认数据
    u8 kv_data[SAVE_UNIT8_SIZE];
    u8 kv_no_data = 0;
    memset(kv_data,0xFF,SAVE_UNIT8_SIZE);
    if(0 == app_storage_read(0,kv_data,SAVE_VALUE_SIZE)){
        kv_no_data = 1;
    }
    
    //读取存储在flash中的低功耗模式，如果有历史数据，则用历史数据，如果没有则用默认数据
    low_power_kind_e low_power_kind;
    u8 mesh_local_control_mode;
    u16 pub_address;

    low_power_kind = ty_uart_cmd_server_for_sig_mesh_uart_common.get_low_power_mode();
    mesh_local_control_mode = ty_uart_cmd_server_for_sig_mesh_uart_common.get_mesh_local_control_mode();

    if(kv_no_data == 1){
        kv_data[KEY_OFFSET_LOW_POWER_FLAG] = low_power_kind; 
        kv_data[KEY_OFFSET_MESH_LOCAL_CONTROL_MODE] = mesh_local_control_mode;
        kv_data[KEY_OFFSET_PUBADDRESS] = 0x00;
        kv_data[KEY_OFFSET_PUBADDRESS+1] = 0x00;
    }else{
        if(kv_data[KEY_OFFSET_LOW_POWER_FLAG] == 0xFF){
            kv_data[KEY_OFFSET_LOW_POWER_FLAG] = low_power_kind;
        }
        if(kv_data[KEY_OFFSET_MESH_LOCAL_CONTROL_MODE] == 0xFF){
            kv_data[KEY_OFFSET_MESH_LOCAL_CONTROL_MODE] = mesh_local_control_mode;
        }
        if(kv_data[KEY_OFFSET_PUBADDRESS] == 0xFF && kv_data[KEY_OFFSET_PUBADDRESS+1] == 0xFF){
            kv_data[KEY_OFFSET_PUBADDRESS] = 0x00;
            kv_data[KEY_OFFSET_PUBADDRESS+1] = 0x00;
        }
    }
    low_power_kind = kv_data[KEY_OFFSET_LOW_POWER_FLAG];
    mesh_local_control_mode = kv_data[KEY_OFFSET_MESH_LOCAL_CONTROL_MODE];
    pub_address = (kv_data[KEY_OFFSET_PUBADDRESS] << 8) + kv_data[KEY_OFFSET_PUBADDRESS+1];

    ty_uart_cmd_server_for_sig_mesh_uart_common.set_low_power_mode(low_power_kind);
    ty_uart_cmd_server_for_sig_mesh_uart_common.set_mesh_local_control_mode(mesh_local_control_mode);
    ty_uart_cmd_server_for_sig_mesh_uart_common.set_mesh_local_control_pub_address(pub_address);

    app_storage_save(0,kv_data,SAVE_VALUE_SIZE);
}

int app_mcu_protocol_cmd(u8 cmd, u8 *data, u8 len){
    ty_uart_cmd_server_for_sig_mesh_uart_common.receive_cmd(cmd,data,len);       
}

int app_mcu_protocol_run(void){
    static u8 work_state = 0;
    static low_power_kind_e low_power_kind = LOW_POWER_DISABLE;
    static u8 mesh_local_control_mode = 0;

    if(work_state != get_if_prov_success()){//mesh状态改变
        work_state = !work_state;
        ty_uart_cmd_server_for_sig_mesh_uart_common.set_work_state(work_state == 0?0:2);
    }

    //low power 状态有变化，则存储
    if(low_power_kind != ty_uart_cmd_server_for_sig_mesh_uart_common.get_low_power_mode()){
        u8 kv_data[1];
        low_power_kind = ty_uart_cmd_server_for_sig_mesh_uart_common.get_low_power_mode();
        kv_data[0] = low_power_kind; 
        app_storage_save(KEY_OFFSET_LOW_POWER_FLAG,kv_data,1);
    }

    //mode local control mode 状态有变化，则存储
    if(mesh_local_control_mode != ty_uart_cmd_server_for_sig_mesh_uart_common.get_mesh_local_control_mode()){
        u8 kv_data[1];
        mesh_local_control_mode = ty_uart_cmd_server_for_sig_mesh_uart_common.get_mesh_local_control_mode();
        kv_data[0] = mesh_local_control_mode; 
        app_storage_save(KEY_OFFSET_MESH_LOCAL_CONTROL_MODE,kv_data,1);

        if(mesh_local_control_mode == 1){//具备 pub address 申请的时候关闭快速配网
            tuya_mesh_fast_prov_en(0);
        }
    }

    if(!app_factory_test_if_enter())
        ty_uart_cmd_server_for_sig_mesh_uart_common.run();
}

////////////////////////////////////////////////////////////////
#define MESH_IS_BROADCAST_ADDR(addr)            ((addr) == 0xFFFF)
#define MESH_IS_GROUP_ADDR(addr)                (((addr) & 0xC000) == 0xC000)
#define MESH_IS_VIRTUAL_ADDR(addr)              (((addr) & 0xC000) == 0x8000)

#define TX_PUBLIC_ADDRESS 0xD000
#define TX_NULL_ADDRESS 0x0000
#define TIMEOUT_GET_RESPONSE_US 2000000

#define F_MESH_CMD       0
#define F_MESH_DATA      1
#define F_MESH_HEAD_LEN  1
#define F_MESH_MIN_LEN   4   //cmd+len+DP_MIN_LEN
#define F_MESH_MAX_LEN   0xFF

#define DP_MIN_LEN       3
#define DP_HEAD_LEN_NVAR 2
#define DP_HEAD_LEN_VAR  3
#define DP_HEAD_LEN_STD  4
#define DP_TYPE_RAW      0x00
#define DP_TYPE_BOOL     0x01
#define DP_TYPE_VALUE    0x02
#define DP_TYPE_STRING   0x03
#define DP_TYPE_ENUM     0x04
#define DP_TYPE_BITMAP   0x05

u16 ad_tx_adress = TX_PUBLIC_ADDRESS;
int wait_get_response_timer_cb(void){
    ad_tx_adress = TX_PUBLIC_ADDRESS;
    return -1;
}

#define MAX_DP 30//最多支持30个DP一起来
#pragma pack (1)
typedef struct{
    u8 id;
    u8 type;
    union{
        struct{//固定长度dp数据
            u8 data;
        }data1;
        struct{//可变长度dp数据
            u8 len;
            u8 data;
        }data2;
        struct{//标准格式dp数据
            u8 len1;
            u8 len2;
            u8 data;
        }data3;
    }value;
}dp_s;
#pragma pack()

int app_mesh_vendor_get_dps(u8 *buf, u8 buf_left_size, u8 *buf_used_size, u8 *para, u8 len, u8 is_std2nstd){
    if(len < DP_MIN_LEN)return 0;
    u8 *p = &buf[*buf_used_size];
    dp_s *q = (dp_s *)para;

    u8 dp_value_len = 0;
    u8 dp_len = 0;
    u8 index = 0;

    switch(q->type){
        case DP_TYPE_RAW:;
        case DP_TYPE_STRING:;
        case DP_TYPE_BITMAP:
            if(is_std2nstd){//std dp to not std dp
                dp_value_len = q->value.data3.len2;
                dp_len = dp_value_len + DP_HEAD_LEN_STD;
                if(dp_len > len)return 0;
                if(DP_HEAD_LEN_VAR + dp_value_len > buf_left_size)return 0;
                p[index++] = q->id;
                p[index++] = q->type;
                p[index++] = dp_value_len;
                memcpy(&p[index],&(q->value.data3.data),dp_value_len);
                index += dp_value_len;               
            }else{//not std dp to std dp
                dp_value_len = q->value.data2.len;
                dp_len = dp_value_len + DP_HEAD_LEN_VAR;
                if(dp_len > len)return 0;                  
                if(DP_HEAD_LEN_STD+dp_value_len > buf_left_size)return 0;
                p[index++] = q->id;
                p[index++] = q->type;
                p[index++] = 0;
                p[index++] = dp_value_len;
                memcpy(&p[index],&(q->value.data2.data),dp_value_len);
                index += dp_value_len;
            }
            break;
        case DP_TYPE_BOOL:
        case DP_TYPE_ENUM:
        case DP_TYPE_VALUE:
            if(is_std2nstd){
                dp_value_len = q->value.data3.len2;
                dp_len = dp_value_len + DP_HEAD_LEN_STD;
                if(dp_len > len)return 0;
                if(DP_HEAD_LEN_NVAR + dp_value_len > buf_left_size)return 0;
                p[index++] = q->id;
                p[index++] = q->type;
                memcpy(&p[index],&(q->value.data3.data),dp_value_len);
                index += dp_value_len;               
            }else{
                dp_value_len = (q->type == DP_TYPE_VALUE ? 4:1);
                dp_len = dp_value_len + DP_HEAD_LEN_NVAR;
                if(dp_len > len)return 0;
                if(DP_HEAD_LEN_STD+dp_value_len > buf_left_size)return 0;
                p[index++] = q->id;
                p[index++] = q->type;
                p[index++] = 0;
                p[index++] = dp_value_len;
                memcpy(&p[index],&(q->value.data1.data),dp_value_len);
                index += dp_value_len;
            }
            break;
        default:
            return 0;
            break;
    }

    *buf_used_size += index;
    buf_left_size -= index;
    if(dp_len < len){
        return app_mesh_vendor_get_dps(buf,buf_left_size, buf_used_size, &para[dp_len],len-dp_len,is_std2nstd);
    }else if(dp_len == len){
        return 1;
    }else{
        return 0;
    }
}

int app_mesh_vendor_send_dps(u8 *para, u8 len){
   
    u8 index = 0;
    u8 dp_len = 0;

    while(1<2){
        dp_len = para[index+3] + 4;
        ty_uart_cmd_server_for_sig_mesh_uart_common.send_cmd(CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_DOWNLOAD,&para[index],dp_len);
        index += dp_len;
        if(index >= len)return 1;
    }
    
    return 1;
}

int app_mesh_vendor_write(u16 adr_src, u16 adr_dst, u8 *para, u8 len, u8 is_ack){

    if(len < F_MESH_MIN_LEN)return 0;
    u8 cmd = para[F_MESH_CMD];

    //解析dp，看看是可变长DP还是非可变长DP
    switch(cmd){
        case 0x01:{//DP cmd
            //    drv_sig_mesh_rf_ad_tx(0,adr_src,para,len);     
            u8 send[F_MESH_MAX_LEN];
            u8 send_len = 0;
            if(app_mesh_vendor_get_dps(send,F_MESH_MAX_LEN,&send_len,&para[F_MESH_DATA],len-1,0)){
                app_mesh_vendor_send_dps(send,send_len);
                ty_timer_event_delete(&wait_get_response_timer_cb);
                ad_tx_adress = adr_src;
                if(MESH_IS_BROADCAST_ADDR(adr_dst) || MESH_IS_GROUP_ADDR(adr_dst) || (MESH_IS_VIRTUAL_ADDR(adr_dst)))
                    ad_tx_adress = TX_NULL_ADDRESS;
                ty_timer_event_add(&wait_get_response_timer_cb,TIMEOUT_GET_RESPONSE_US);
            }
            break;
        }
        case 0x81:{//配置设备订阅虚拟地址
                    /*
              if(para[F_MESH_HEAD_LEN] == 3){
                  u16 group_addr = (para[F_MESH_HEAD_LEN+2] << 8) + para[F_MESH_HEAD_LEN+3];
                  APP_LOG("vd_group_add: %04x\r\n",group_addr);
                  u16 op_code = para[F_MESH_HEAD_LEN+1]? CFG_MODEL_SUB_ADD : CFG_MODEL_SUB_DEL;
                  //total 8, if add 9st return error
                  cfg_cmd_sub_set(op_code, ele_adr_primary, ele_adr_primary, group_addr, VENDOR_MD_TUYA_LIGHT_S, 0);
              } 
              */
            break;
        }
        case 0x82:{//APP查询当前群组内设备
            
            break;
        }
        case 0x86:{//配置设备主动pub地址
            u8 ret =  app_storage_save(KEY_OFFSET_PUBADDRESS,&para[F_MESH_HEAD_LEN+1],2);
            u8 data[3] = {0x86,0x01,0x00};
            data[2] = (ret == 0?1:0);
            app_mesh_vendor_ad_tx(adr_dst,adr_src,data,3,0);

            u16 pub_address = (para[F_MESH_HEAD_LEN+1] << 8) + para[F_MESH_HEAD_LEN+2];
            ty_uart_cmd_server_for_sig_mesh_uart_common.set_mesh_local_control_pub_address(pub_address);
            break;
        }
    }

    return 0;
}

int app_mesh_vendor_read(u16 adr_src, u16 adr_dst, u8 *para, u8 len, u8 is_ack){
    static u32 now_time = 0;

    if(len < 3)return 0;//CMD+LEN+DATA
    u8 cmd = para[F_MESH_CMD];
    u8 data_len = para[F_MESH_HEAD_LEN];
    //if((data_len == 1) && (para[F_MESH_HEAD_LEN+1] == 0)){
    //query cmd only support query all, not support query one or multi dps
    //but the app will send query one dp cmd to gateway to node
    //therefor, every get query cmd(don't care whether it's query all or one dp), just use query all
    //for stop multi use query all cmd, make a 2s delay
    if(hal_clock_time_exceed(now_time,2000000)){
        now_time = hal_clock_get_system_tick();
        ty_uart_cmd_server_for_sig_mesh_uart_common.send_cmd(CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_QUERY_ALL,NULL,0);
        ty_timer_event_delete(&wait_get_response_timer_cb);
        ad_tx_adress = adr_src;
        ty_timer_event_add(&wait_get_response_timer_cb,TIMEOUT_GET_RESPONSE_US);
        //}else{  
        //}
    }

    return 1;
}


void app_mesh_vendor_ad_tx(u16 adr_src, u16 adr_dst, u8 *params, u8 len, u8 is_use_params_adr){
    u8 send[F_MESH_MAX_LEN] = {0x01};
    u8 send_len = 0;
    if(app_mesh_vendor_get_dps(&send[1],F_MESH_MAX_LEN-1,&send_len,params,len,1)){
        if(is_use_params_adr == 1){
            tuya_mesh_data_send(0, adr_dst, TUYA_VD_TUYA_WTITE, send, send_len+1, 0, 0);
        }else{
            if(ad_tx_adress != TX_NULL_ADDRESS){
                tuya_mesh_data_send(0, ad_tx_adress, TUYA_VD_TUYA_DATA, send, send_len+1, 0, 0);
            }
        }
        ty_timer_event_delete(&wait_get_response_timer_cb);
        ty_timer_event_add(&wait_get_response_timer_cb,TIMEOUT_GET_RESPONSE_US);
    }
}
