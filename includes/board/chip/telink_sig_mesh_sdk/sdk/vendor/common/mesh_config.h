/********************************************************************************************************
 * @file     mesh_config.h 
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

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif
//------------hardware parameters
// HCI Select
#define PROXY_HCI_GATT			1
#define PROXY_HCI_USB			2
#define PROXY_HCI_SEL			PROXY_HCI_GATT

#define GATEWAY_MODEL_PLUS_EN   0

#define DEBUG_MESH_DONGLE_IN_VC_EN		0


#define SHOW_VC_SELF_NO_NW_ENC		1
#define SHOW_VC_SELF_NW_ENC			2	// can not send reliable cmd with segment, such as netkey add,...


#define NODE_CAN_SEND_ADV_FLAG			1		// must 1
#define DEBUG_SHOW_VC_SELF_EN			0		// must 0
#define VC_CHECK_NEXT_SEGMENT_EN		0		// must 0
#define DEBUG_VENDOR_CMD_EN 		    0
#define VC_SUPPORT_ANY_VENDOR_CMD_EN	0		// should be 0

//------------ project define-------------
#define PROJECT_VC_DONGLE 	1
#define PROJECT_VC_MESH 	2
#define PROJECT_VC_MAX 		10	// VC project max
#define PROJECT_FW_MESH		11	//FW start from 11

#define PROJECT_SEL			PROJECT_FW_MESH

#define IS_VC_PROJECT			(PROJECT_SEL <= PROJECT_VC_MAX)
#define IS_VC_PROJECT_MASTER	0

#define PROXY_GATT_WITH_HEAD  0

#define BEACON_ENABLE			0
//ms, should be multiple of 10
#define BEACON_INTERVAL			100

#define ATT_TAB_SWITCH_ENABLE 	1

#define PTS_TEST_EN                 0
#define DEBUG_EVB_EN 		        0   // just telink internal used, don't modity

#define LPN_VENDOR_SENSOR_EN        0

//------------ mesh config-------------
#define MD_CFG_CLIENT_EN            0   // don't modify
#define RELIABLE_CMD_EN             0   // don't modify

//------------ mesh config (user can config)-------------
#define MESH_NORMAL_MODE		0
#define MESH_CLOUD_ENABLE		1
#define MESH_SPIRIT_ENABLE		2// use this mode should burn in the para in 0x78000,or use init para should enable the  con_sec_data
#define MESH_AES_ENABLE 		3
#define MESH_GN_ENABLE 		    4
#define MESH_MI_ENABLE          5
#define MESH_MI_SPIRIT_ENABLE   6   // dual vendor
#define MESH_IRONMAN_MENLO_ENABLE   7   // inclue boot_loader.bin and light.bin
#define MESH_ZB_BL_DUAL_ENABLE      8   // mesh && zigbee normal dual mode with bootloader


#define MESH_USER_DEFINE_MODE 	MESH_NORMAL_MODE

// vendor id list
#define SHA256_BLE_MESH_PID		0x01A8
#define VENDOR_ID_MI		    0x038F

// mi product type 
#define MI_PRODUCT_TYPE_CT_LIGHT		0x01
#define MI_PRODUCT_TYPE_LAMP			0x02


#define MI_PRODUCT_TYPE_ONE_ONOFF		0x11
#define MI_PRODUCT_TYPE_TWO_ONOFF		0x12
#define MI_PRODUCT_TYPE_THREE_ONOFF		0x13

#define MI_PRODUCT_TYPE_PLUG			0x21
#define MI_PRODUCT_TYPE_FANS			0x30

// SHARE subscription list and publish address
#if(MESH_USER_DEFINE_MODE == MESH_NORMAL_MODE)
#define SUBSCRIPTION_SHARE_EN		1
#define PROVISION_FLOW_SIMPLE_EN    0
#endif

#define AIS_ENABLE					0

#ifndef NL_API_ENABLE
#define NL_API_ENABLE 0
#endif
#ifndef FW_START_BY_BOOTLOADER_EN
#define FW_START_BY_BOOTLOADER_EN  0
#endif

#ifndef DUAL_MESH_ZB_BL_EN
#define DUAL_MESH_ZB_BL_EN  0
#endif



#define SPIRIT_PRIVATE_LPN_EN		0

#define VENDOR_MD_NORMAL_EN         1   // include ali

#define LIGHT_TYPE_NONE				0
#define LIGHT_TYPE_CT				1
#define LIGHT_TYPE_HSL				2
#define LIGHT_TYPE_XYL				3
#define LIGHT_TYPE_POWER			4
#define LIGHT_TYPE_CT_HSL			5
#define LIGHT_TYPE_DIM			    6   // only single PWM
#define LIGHT_TYPE_PANEL			7   // only ONOFF model
#define LIGHT_TYPE_LPN_ONOFF_LEVEL  8   // only ONOFF , LEVEL model
#define TYPE_TOOTH_BRUSH			9

#define LIGHT_TYPE_SEL				LIGHT_TYPE_CT_HSL	// 


#define MD_LIGHT_CONTROL_EN			0	// must 0
#define MD_LEVEL_EN                 0   // must 1
#define CMD_LINEAR_EN               0

#define MESH_RX_TEST	0
#define MESH_DELAY_TEST_EN		0
#define MD_MESH_OTA_EN				0   // dufault disable before released by SIG.



#define DISTRIBUTOR_UPDATE_CLIENT_EN    0

#define DIRECTED_FORWARDING_MODULE_EN	0
#define DF_TEST_MODE_EN  				0

#define MD_ONOFF_EN                 1   // must 1
#define SENSOR_LIGHTING_CTRL_EN     0


#define MD_DEF_TRANSIT_TIME_EN      0

#define MD_POWER_ONOFF_EN           0 	// because both of them save in same flash sector.
#define MD_TIME_EN                  0
#define MD_SCENE_EN                 0
#define MD_SCHEDULE_EN              0  // because both of them save in same flash sector.
#define MD_PROPERTY_EN				0
#define	MD_LOCATION_EN				0	// location,sensor,battery use same flash addr, but one sector max store 6 models
#define MD_SENSOR_EN				0	
#define MD_BATTERY_EN				0

#define MD_SERVER_EN                1   // SIG and vendor MD
#define MD_CLIENT_EN                0   // just SIG MD

#define MD_REMOTE_PROV              0   // must 0, only project_mesh support now. dufault disable before released by SIG.

#define STRUCT_MD_TIME_SCHEDULE_EN          0
#define STRUCT_MD_DEF_TRANSIT_TIME_POWER_ONOFF_EN   0

#define FACTORY_TEST_MODE_ENABLE    1
#define MANUAL_FACTORY_RESET_TX_STATUS_EN       0
#define KEEP_ONOFF_STATE_AFTER_OTA	0

//------------ mesh config(user can config) end -------------

/*ELE_CNT_EVERY_LIGHT means element count of one instance*/
#define ELE_CNT_EVERY_LIGHT         1   // APP and gateway use 1 element always,


#define DEBUG_VC_FUNCTION			0
#define DEBUG_BLE_EVENT_ENABLE 		0
#define DEBUG_PREINSTALL_APP_KEY_EN 0

#define REFRESH_ST_BY_HW_EN			0

#ifndef MESH_MONITOR_EN
#define MESH_MONITOR_EN 			0
#endif

#define MD_BIND_WHITE_LIST_EN 		0
// feture part ,enable or disable to cut down the ram cost 

#define FEATURE_FRIEND_EN 		1   // WIN 32 should be suport disable: model_sig_cfg_s.frid
#define FEATURE_LOWPOWER_EN		0
#define FEATURE_PROV_EN 		1
    #if (0 == NODE_CAN_SEND_ADV_FLAG)
#define FEATURE_RELAY_EN		0	// must 0, because it must be proxyed by another node. and messages havee been relay by this node.
#define FEATURE_PROXY_EN 		0	// must 0, 
    #else
#define FEATURE_RELAY_EN		1
#define FEATURE_PROXY_EN 		1
    #endif

#if FEATURE_FRIEND_EN
#define MAX_LPN_NUM					2   // should be less than or equal to 16
#define FN_PRIVATE_SEG_CACHE_EN     0   // not push all segments to friend cache at the same time
#else
#define MAX_LPN_NUM					0   // must 0
#endif

#define DEBUG_PROXY_FRIEND_SHIP		0
#define PROXY_FRIEND_SHIP_MAC_FN	(0x82690014)
#define PROXY_FRIEND_SHIP_MAC_LPN1	(0x82690015)
#define PROXY_FRIEND_SHIP_MAC_LPN2	(0x82690016)

#define DEBUG_IV_UPDATE_TEST_EN     (0)

#define USER_DEFINE_SET_CCC_ENABLE 	1   // must 1

#define PROXY_PDU_TIMEOUT_TICK 		20*1000*1000
#define SEND_STATUS_WHEN_POWER_ON			1


// flash save flag 
#define SAVE_FLAG_PRE	(0xAF)
#define SAVE_FLAG       (0xA5)

//------------ mesh keycode-------------
#define	RC_KEY_1_ON			0x01
#define	RC_KEY_1_OFF		0x02
#define	RC_KEY_2_ON			0x03
#define	RC_KEY_2_OFF		0x04
#define	RC_KEY_3_ON			0x05
#define	RC_KEY_3_OFF		0x06
#define	RC_KEY_4_ON			0x07
#define	RC_KEY_4_OFF		0x08
#define	RC_KEY_A_ON			0x09
#define	RC_KEY_A_OFF		0x0a
#define	RC_KEY_UP			0x0b
#define	RC_KEY_DN			0x0c
#define	RC_KEY_L			0x0d
#define	RC_KEY_R			0x0e
#define	RC_KEY_M			0x0f

//-------------CMD
#define REPORT_KEY_ONLY_EN		0

#define			LGT_CMD_LIGHT_ON				0x10
#define			LGT_CMD_LIGHT_OFF				0x11//internal use
#define			LGT_CMD_LUM_UP					0x12//internal use
#define			LGT_CMD_LUM_DOWN				0x13//internal use
#define			LGT_CMD_LEFT_KEY				0x14//internal use
#define			LGT_CMD_RIGHT_KEY				0x15//internal use

#define			IRQ_TIME1_INTERVAL			    (1000) // unit: us
#define			IRQ_GPIO_ENABLE  			    0


/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
