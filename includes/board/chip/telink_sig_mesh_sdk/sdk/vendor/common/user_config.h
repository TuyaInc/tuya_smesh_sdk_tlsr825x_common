/********************************************************************************************************
 * @file     user_config.h 
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

#include "../../proj/mcu/config.h"


#if (__TUYA_PROJECT__)
	#if(MCU_CORE_TYPE == MCU_CORE_8269)
	#include "../base/app_config_8269.h"
	#elif(MCU_CORE_TYPE == MCU_CORE_8258)
	#include "../base/app_config_8258.h"
	#endif
#else
    #if(MCU_CORE_TYPE == MCU_CORE_8269)
    #include "../mesh/app_config_8269.h"
    #elif(MCU_CORE_TYPE == MCU_CORE_8258)
    #include "../mesh/app_config_8258.h"
    #elif(MCU_CORE_TYPE == MCU_CORE_8278)
    #include "../mesh/app_config_8278.h"
    #endif
#endif


