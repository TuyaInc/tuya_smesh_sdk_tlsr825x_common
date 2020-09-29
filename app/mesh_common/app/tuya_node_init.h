/*************************************************************************
	> File Name: tuya_node_init.h
	> Author: 
	> Mail: 
	> Created Time: Mon 25 Mar 2019 13:55:08 CST
 ************************************************************************/

#ifndef _APP_UNPROV_BEACON_H
#define _APP_UNPROV_BEACON_H

#include "board.h"

extern void mesh_para_init(void);

uint16_t tuya_get_mesh_category(void);
uint8_t* tuya_get_pid(void);
uint8_t tuya_get_is_key_or_pid(void);
uint8_t tuya_get_if_need_pub_addr(void);
uint16_t tuya_get_firmware_version(void);
uint8_t tuya_get_power_reset_cnt(void);
uint8_t tuya_get_power_reset_time(void);
uint8_t tuya_get_power_reset_recover_time(void);

void tuya_pid_set(uint8_t *pid);
void tuya_mesh_category_set(uint16_t mesh_category);


    
#endif
