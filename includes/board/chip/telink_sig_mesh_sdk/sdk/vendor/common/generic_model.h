/********************************************************************************************************
 * @file     generic_model.h 
 *
 * @brief    for TLSR chips
 *
 * @author	 telink
 * @date     Sep. 30, 2010
 *
 * @par      Copyright (c) 2010, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *           
 *			 The information contained herein is confidential and proprietary property of Telink 
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms 
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai) 
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in. 
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this 
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided. 
 *           
 *******************************************************************************************************/

#pragma once

#include "../../proj/tl_common.h"
#include "../../proj_lib/sig_mesh/app_mesh.h"

/** @addtogroup Mesh_Common
  * @{
  */


/** @addtogroup General_Model
  * @brief General Models Code.
  * @{
  */


//----------------------------------- op code
// op cmd 0xxxxxxx (SIG)

// op cmd 10xxxxxx xxxxxxxx (SIG)

//------------------vendor op end-------------------

extern u16 size_page0;


int g_onoff_set(mesh_cmd_g_onoff_set_t *p_set, int par_len, int force_last, int idx, u8 retransaction, st_pub_list_t *pub_list);


/**
  * @}
  */
    
/**
  * @}
  */


#define mesh_cmd_sig_g_level_status         (0)
#define mesh_cmd_sig_def_trans_time_status  (0)
#define mesh_cmd_sig_g_on_powerup_status    (0)
#define mesh_cmd_sig_g_power_status         (0)
#define mesh_cmd_sig_g_power_last_status    (0)
#define mesh_cmd_sig_g_power_def_status     (0)
#define mesh_cmd_sig_g_power_range_status   (0)
#define mesh_cmd_sig_g_battery_status       (0)
#define mesh_cmd_sig_g_location_global_status   (0)
#define mesh_cmd_sig_g_location_local_status    (0)
// -----------

