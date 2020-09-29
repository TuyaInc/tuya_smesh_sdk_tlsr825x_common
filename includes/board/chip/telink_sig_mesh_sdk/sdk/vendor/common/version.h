/********************************************************************************************************
 * @file     version.h 
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

// can't use "enum" here, because cstartup.S not support

//#define   BUILD_VERSION  	"Revision: 45:49M"
//#define   BUILD_TIME  		"2012-07-24-21:37:43"

#include "../../proj/mcu/config.h"
#include "mesh_config.h"


#define PID_UNKNOW              (0x0000)
// ------ light ------
// LIGHT_TYPE_SEL_
// ------ gateway ------
#define PID_GATEWAY             (0x0101)
// ------ LPN ------
#define PID_LPN                 (0x0201)
// ------ SWITCH ------
#define PID_SWITCH              (0x0301)
// ------ SPIRIT_LPN ------
#define PID_SPIRIT_LPN          (0x0401)

/*
MESH_PID_SEL : PID is product ID,
MESH_VID: VID is software version ID,

PID and VID are used in composition data: model_sig_cfg_s_cps.
format: please refer to spec "4.2.1.1 Composition Data Page 0"
*/

#define MESH_PID_SEL		(0x0000)

#define MESH_PID_REAL  MESH_PID_SEL

// -- 
#define RUN_254K_IN_20000_EN 0 // enable to run 254K in 0x20000(default is 124k), disable to save RAM	

#define MCU_RUN_SRAM_WITH_CACHE_EN      0   // 

#define MCU_RUN_SRAM_EN                 0   // manual set data address in boot.link.can't read flash by pointer 


#define MCU_STACK_INIT_EN               (1)

