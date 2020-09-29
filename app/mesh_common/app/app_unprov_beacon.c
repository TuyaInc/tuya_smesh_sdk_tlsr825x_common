/*************************************************************************
	> File Name: app_unprov_beacon.c
	> Author: 
	> Mail: 
	> Created Time: Mon 25 Mar 2019 13:55:04 CST
 ************************************************************************/
#include "ty_nv.h"
#include "tuya_node_init.h"


#define NV_USER3_ITEM_PID 0
#define PID_LEN 8


void app_unprov_beacon_init(void){
    u8 pid[PID_LEN];

    if(NV_SUCCESS == ty_nv_user_data_read(NV_USER3_ITEM_PID, PID_LEN, pid)){
        tuya_pid_set(pid);
    }
}

void app_unprov_beacon_update_pid(u8 *pid, u8 len){
    if(len != PID_LEN)return;

    u8 pid_nv[PID_LEN];

    if(NV_SUCCESS == ty_nv_user_data_read(NV_USER3_ITEM_PID, PID_LEN, pid_nv)){
        if(memcmp(pid,pid_nv,PID_LEN) != 0){
            if(NV_SUCCESS != ty_nv_user_data_write(NV_USER3_ITEM_PID, PID_LEN, pid)){
                ty_nv_user_data_erase();
                ty_nv_user_data_write(NV_USER3_ITEM_PID, PID_LEN, pid);
            }    
        }
    }else{
        if(NV_SUCCESS != ty_nv_user_data_write(NV_USER3_ITEM_PID, PID_LEN, pid)){
            ty_nv_user_data_erase();
            ty_nv_user_data_write(NV_USER3_ITEM_PID, PID_LEN, pid);
        }    
    }

    tuya_pid_set(pid);
}
