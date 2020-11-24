/*
 * ty_fast_provision.h
 *
 *  Created on: 2020-05-28
 *      Author: Joey
 */

#ifndef __TY_FAST_PROVISION_H
#define __TY_FAST_PROVISION_H
#include "ty_nv.h"
#include "tuya_sigmesh_hal.h"

#define FAST_PROVISION_TIMEOUT 		60*1000*1000

enum{
	FAST_PROV_IDLE,
	FAST_PROV_INFO_GET,
	FAST_PROV_SET_ADDR,
	FAST_PROV_PROV_DATA_SET,
	FAST_PROV_CONFIRM,
	FAST_PROV_COMPLETE,
	FAST_PROV_TIME_OUT,
};


typedef struct{
	u16 category;
	u16 ele_addr;
}dev_info_get_t;

typedef struct{
	u8 mac[6];
	u16 category;	
}fast_prov_info_st;

typedef struct{
	fast_prov_net_data_t pro_data;
	fast_prov_app_key_t appkey_set;
}fast_prov_net_info_t;

typedef struct{
	u16 ele_addr;
	u8 bind_kind;
	u8 mesh_pid[8];
	u16 dev_ver;
//	u8 extra_info;
} _PACKED_ fast_prov_mac_st;

typedef struct{
	u8 err_type;
	u8 err_rfu;
}fast_prov_mac_err_st;

typedef struct{
	u8 get_mac_en;
	u32 rcv_op;
	u8 cur_sts;
	u8 last_sts;
	u8 pending;
	u16 delay;
	u32 start_tick;
	u32 revert_tick;
	fast_prov_net_info_t net_info;
} _PACKED_ fast_prov_par_t;

void ty_mesh_fast_prov_init();
void ty_mesh_fast_prov_proc(void);
void tuya_mesh_fast_prov_en(u8 flag);
uint8_t get_fast_prov_en_state(void);

#endif
