/********************************************************************************************************
 * @file     blt_config.h 
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

//////////////////////////////////////////////////////////////////////////////
/**
 *  @brief  Definition for Device info
 */
#include "proj/mcu/config.h"
#include "../rf_drv.h"
#include "../../proj/tl_common.h"
#include "../../vendor/common/dual_mode_adapt.h"
#include "../pm.h"

#define PA_ENABLE	0
#if(PA_ENABLE)
#if(MCU_CORE_TYPE == MCU_CORE_8269)
#define		MY_RF_POWER_INDEX		RF_POWER_0dBm
#elif(MCU_CORE_TYPE == MCU_CORE_8258)
#define		MY_RF_POWER_INDEX		RF_POWER_P0p04dBm
#elif(MCU_CORE_TYPE == MCU_CORE_8278)
#define		MY_RF_POWER_INDEX		RF_POWER_N0p28dBm
#endif
#else
#if(MCU_CORE_TYPE == MCU_CORE_8269)
#define		MY_RF_POWER_INDEX		RF_POWER_8dBm
#elif(MCU_CORE_TYPE == MCU_CORE_8258)
#define		MY_RF_POWER_INDEX		RF_POWER_P10p46dBm
#elif(MCU_CORE_TYPE == MCU_CORE_8278)
#define		MY_RF_POWER_INDEX		RF_POWER_P3p50dBm
#endif
#endif

#define  MAX_DEV_NAME_LEN 				18

#ifndef DEV_NAME
#define DEV_NAME                        "tModule"
#endif

#define RAMCODE_OPTIMIZE_CONN_POWER_NEGLECT_ENABLE			0

enum{
	TYPE_TLK_MESH		    = 0x000000A3,// don't change, must same with telink mesh SDK
	TYPE_SIG_MESH		    = 0x0000003A,// don't change, must same with telink mesh SDK
	TYPE_TLK_BLE_SDK	    = 0x000000C3,// don't change, must same with telink mesh SDK
	TYPE_TLK_ZIGBEE 	    = 0x0000003C,// don't change, must same with telink mesh SDK
    TYPE_DUAL_MODE_STANDBY  = 0x00000065,// dual mode state was standby to be selected
	TYPE_DUAL_MODE_RECOVER 	= 0x00000056,// don't change, must same with zigbee SDK, recover from zigbee.
    TYPE_DUAL_MODE_ZIGBEE_RESET  = 0x00000053,// don't change.
};


/** Calibration Information FLash Address Offset of  CFG_ADR_CALIBRATION_xx_FLASH ***/
#define		CALIB_OFFSET_CAP_INFO								(0x0)
#define		CALIB_OFFSET_TP_INFO								(0x40)
#define		OFFSET_CUST_RC32K_CAP_INFO                          (0x80)
/** Calibration Information end ***/

/**************************** 512 K Flash *****************************/
#define		CFG_ADR_MAC_512K_FLASH								0x76000 // don't change
#define		CFG_ADR_CALIBRATION_512K_FLASH						0x77000 // don't change

/**************************** 1 M Flash *******************************/
#define		CFG_ADR_MAC_1M_FLASH		   						0xFF000 // don't change
#define		CFG_ADR_CALIBRATION_1M_FLASH						0xFE000 // don't change

#if FLASH_1M_ENABLE
#define		CFG_SECTOR_ADR_MAC_CODE		        CFG_ADR_MAC_1M_FLASH
#define		CFG_SECTOR_ADR_CALIBRATION_CODE     CFG_ADR_CALIBRATION_1M_FLASH
#else
#define		CFG_SECTOR_ADR_MAC_CODE		        CFG_ADR_MAC_512K_FLASH
#define		CFG_SECTOR_ADR_CALIBRATION_CODE     CFG_ADR_CALIBRATION_512K_FLASH
#endif

#if ((MCU_CORE_TYPE == MCU_CORE_8267)||(MCU_CORE_TYPE == MCU_CORE_8269))
#define AUTO_ADAPT_MAC_ADDR_TO_FLASH_TYPE_EN    (0) // must 0
#else
#define AUTO_ADAPT_MAC_ADDR_TO_FLASH_TYPE_EN    ((CFG_SECTOR_ADR_MAC_CODE == CFG_ADR_MAC_512K_FLASH)||(CFG_SECTOR_ADR_MAC_CODE == CFG_ADR_MAC_1M_FLASH))
#endif

/////////////////// Flash  Address Config ////////////////////////////
#define	FLASH_SECTOR_SIZE       (4096)

#define	FLASH_ADDRESS_DEFINE						\
		u32 flash_adr_misc      = FLASH_ADR_MISC;							
#define FLASH_ADDRESS_CONFIG						
		//flash_adr_misc 			= FLASH_ADR_MISC;			
#define FLASH_ADDRESS_EXTERN						\
		extern unsigned int flash_adr_misc;	



#if (0 == FLASH_1M_ENABLE)
#define 		FLASH_ADR_AREA_FIRMWARE_END	0x30000
/* Flash adr 0x00000 ~ 0x2ffff  is firmware area*/
#define			FLASH_ADR_AREA_1_START		0x30000
#define			FLASH_ADR_MESH_KEY			FLASH_ADR_AREA_1_START
#define			FLASH_ADR_MD_CFG_S			0x31000
#define			FLASH_ADR_MD_HEALTH			0x32000
#define			FLASH_ADR_MD_G_ONOFF_LEVEL	0x33000
#define			FLASH_ADR_MD_TIME_SCHEDULE	0x34000
#define			FLASH_ADR_MD_LIGHTNESS		0x35000	// share with power level
#define			FLASH_ADR_MD_LIGHT_CTL		0x36000
#define			FLASH_ADR_MD_LIGHT_LC		0x37000
#define			FLASH_ADR_SW_LEVEL			0x38000
#define 		FLASH_ADR_MD_SENSOR		    0x39000
#define 		FLASH_ADR_PROVISION_CFG_S	0x3a000
#define			FLASH_ADR_MD_LIGHT_HSL		0x3b000 // cps before V23
#define			FLASH_ADR_FRIEND_SHIP		0x3c000
#define			FLASH_ADR_MISC				0x3d000
#define			FLASH_ADR_RESET_CNT			0x3e000
#if WIN32
#define			FLASH_ADR_MD_PROPERTY		0x40000
#else
#define			FLASH_ADR_MD_PROPERTY		0x3f000 // just test
#endif

#define			FLASH_ADR_AREA_1_END		0x40000

/* Flash adr 0x40000 ~ 0x6ffff  is firmware(OTA) area*/
#define			FLASH_ADR_AREA_2_START		0x70000
#define			FLASH_ADR_MD_VD_LIGHT		FLASH_ADR_AREA_2_START
#define			FLASH_ADR_MD_G_POWER_ONOFF	0x71000
#define			FLASH_ADR_MD_SCENE			0x72000

#define			FLASH_ADR_MESH_TYPE_FLAG	0x73000	// don't change, must same with telink mesh SDK
#define			FLASH_ADR_MD_MESH_OTA		0x74000
#define         FLASH_ADR_MD_REMOTE_PROV    0x75000 // remote provision part 

#define			FLASH_ADR_AREA_2_END		0x76000


/*******vendor define here, from 0x7ffff ~ 0x78000 ...
vendor use from 0x7ffff to 0x78000 should be better, because telink may use 0x78000,0x79000 later.
********************************************/

#define			FLASH_ADR_PAR_USER_MAX		0x80000
#else // 1M flash
#if(0 ==SWITCH_FW_ENABLE) // normal mode
    #if PINGPONG_OTA_DISABLE
#define 		FLASH_ADR_AREA_FIRMWARE_END	0x5A000 // 360K
#define         FLASH_ADR_UPDATE_NEW_FW     FLASH_ADR_AREA_FIRMWARE_END
    #else
#define 		FLASH_ADR_AREA_FIRMWARE_END	0x3F000 // 252K
    #endif
/* Flash adr 0x00000 ~ 0x2ffff  is firmware area*/
#define			FLASH_ADR_AREA_1_START		0xB4000 // = FLASH_ADR_AREA_FIRMWARE_END * 2, use same address whether disable pingpong or not.
#define			FLASH_ADR_MESH_KEY			FLASH_ADR_AREA_1_START
#define			FLASH_ADR_MD_CFG_S			0xB5000
#define			FLASH_ADR_MD_HEALTH			0xB6000
#define			FLASH_ADR_MD_G_ONOFF_LEVEL	0xB7000
#define			FLASH_ADR_MD_TIME_SCHEDULE	0xB8000
#define			FLASH_ADR_MD_LIGHTNESS		0xB9000	// share with power level
#define			FLASH_ADR_MD_LIGHT_CTL		0xBA000
#define			FLASH_ADR_MD_LIGHT_LC		0xBB000
#define			FLASH_ADR_SW_LEVEL			0xBC000
#define   		FLASH_ADR_MD_SENSOR			0xBD000
#define 		FLASH_ADR_PROVISION_CFG_S	0xBE000
#define			FLASH_ADR_MD_LIGHT_HSL		0xBF000 // cps before V23
#define			FLASH_ADR_FRIEND_SHIP		0xC0000
#define			FLASH_ADR_MISC				0xC1000
#define			FLASH_ADR_RESET_CNT			0xC2000
// 				                                            0xC3000 // reserve now
#define			FLASH_ADR_MD_PROPERTY		0xC4000 // just test
#define			FLASH_ADR_MD_VD_LIGHT		0xC5000
#define			FLASH_ADR_MD_G_POWER_ONOFF	0xC6000
#define			FLASH_ADR_MD_SCENE			0xC7000
// 				                                            0xC8000 // reserve now
#define			FLASH_ADR_MD_MESH_OTA		0xC9000
#define         FLASH_ADR_MD_REMOTE_PROV    0xCA000 // remote provision part 
#define 		FLASH_ADR_VC_NODE_INFO		0xCB000		//
#define			FLASH_ADR_AREA_1_END		0xCC000
// FLASH_ADR_AREA_1_END to start of user is reserve for telink
/*******SIG mesh vendor define here, from FLASH_ADR_USER_MESH_END ~ FLASH_ADR_USER_MESH_START, vendor define from behined to head should be better, .*/
#define			FLASH_ADR_USER_MESH_START	0xD2000
#define			FLASH_ADR_USER_MESH_END	    0xD8000

/*SIG mesh END*/

// 0xFD000: FLASH_ADR_MESH_TYPE_FLAG; 0xFE000: CUST_CAP_INFO_ADDR;  0xFF000: CFG_ADR_MAC (with FLASH_ADR_EDCH_PARA);  

#else//SWITCH_FW_ENABLE == 1
#define 		FLASH_ADR_AREA_FIRMWARE_END		0x40000 // 256K
#define         FLASH_ADR_LIGHT_TELINK_MESH    	0x80000 
#define         FLASH_ADR_UPDATE_NEW_FW     	0xc0000

#define			FLASH_ADR_AREA_1_START		0x40000 // = FLASH_ADR_AREA_FIRMWARE_END * 2, use same address whether disable pingpong or not.
#define			FLASH_ADR_MESH_KEY			FLASH_ADR_AREA_1_START
#define			FLASH_ADR_MD_CFG_S			0x41000
#define			FLASH_ADR_MD_HEALTH			0x42000
#define			FLASH_ADR_MD_G_ONOFF_LEVEL	0x43000
#define			FLASH_ADR_MD_TIME_SCHEDULE	0x44000
#define			FLASH_ADR_MD_LIGHTNESS		0x45000	// share with power level
#define			FLASH_ADR_MD_LIGHT_CTL		0x46000
#define			FLASH_ADR_MD_LIGHT_LC		0x47000
#define			FLASH_ADR_SW_LEVEL			0x48000
#define   		FLASH_ADR_MD_SENSOR			0x49000
#define 		FLASH_ADR_PROVISION_CFG_S	0x4A000
#define			FLASH_ADR_MD_LIGHT_HSL		0x4B000 // cps before V23
#define			FLASH_ADR_FRIEND_SHIP		0x4C000
#define			FLASH_ADR_MISC				0x4D000
#define			FLASH_ADR_RESET_CNT			0x4E000
#define			FLASH_ADR_MD_PROPERTY		0x4F000 // just test
#define			FLASH_ADR_MD_VD_LIGHT		0x50000
#define			FLASH_ADR_MD_G_POWER_ONOFF	0x51000
#define			FLASH_ADR_MD_SCENE			0x52000
// 				                                            0x53000 // reserve now
#define			FLASH_ADR_MD_MESH_OTA		0x54000
#define         FLASH_ADR_MD_REMOTE_PROV    0x55000 // remote provision part 
#define 		FLASH_ADR_VC_NODE_INFO		0x56000		//
#define			FLASH_ADR_AREA_1_END		0x57000
// FLASH_ADR_AREA_1_END to start of user is reserve for telink
/*******SIG mesh vendor define here, from FLASH_ADR_USER_MESH_END ~ FLASH_ADR_USER_MESH_START, vendor define from behined to head should be better, .*/
#define			FLASH_ADR_USER_MESH_START	0x58000
// TODO
#define			FLASH_ADR_USER_MESH_END	    0x60000
#define			FLASH_ADR_BOOT_FLAG		    0x7F000
/*SIG mesh END*/

// ----
// 0xFD000: FLASH_ADR_MESH_TYPE_FLAG; 0xFE000: CUST_CAP_INFO_ADDR;  0xFF000: CFG_ADR_MAC (with FLASH_ADR_EDCH_PARA);  
#endif /*end of (1 ==SWITCH_FW_ENABLE)*/

#endif /*end of (1 == FLASH_1M_ENABLE)*/

#if 1// common
#if (FLASH_1M_ENABLE)
#define			FLASH_ADR_MESH_TYPE_FLAG	0xFD000	// don't change, must same with telink mesh SDK
#endif

#define		CFG_ADR_MAC					flash_sector_mac_address
#if (0)
//#define		    CUST_CAP_INFO_ADDR			flash_sector_calibration // == (CFG_ADR_MAC + STATIC_ADDR_FREQ_OFFSET)
#define         FLASH_ADR_STATIC_OOB	    (STATIC_ADDR_MESH_STATIC_OOB)
#define         FLASH_ADR_EDCH_PARA		    (FLASH_ADR_EDCH_PARA_SECTOR) // size = 0x68 = sizeof(mesh_ecdh_key_str)
#define 		SECTOR_PAR_SIZE_MAX			        0x100
#else

#define			CFG_ADR_DUAL_MODE_EN		(CFG_SECTOR_ADR_MAC_CODE + 0x80) // use fixed addr

#define			CFG_ADR_DUAL_CALI_VAL_FLAG	(CFG_SECTOR_ADR_MAC_CODE + 0x84) // use for DUAL_MODE_WITH_TLK_MESH_EN
#define			CFG_ADR_DUAL_CALI_VAL		(CFG_SECTOR_ADR_MAC_CODE + 0x88) // use for DUAL_MODE_WITH_TLK_MESH_EN
#define         FLASH_ADR_EDCH_PARA		    (flash_sector_mac_address + 0x100) // size = 0x68 = sizeof(mesh_ecdh_key_str)
#define 		SECTOR_PAR_SIZE_MAX			        0x200
		
	#if((MCU_CORE_TYPE == MCU_CORE_8267)||(MCU_CORE_TYPE == MCU_CORE_8269))
#define		CUST_CAP_INFO_ADDR			(flash_sector_calibration + CALIB_OFFSET_CAP_INFO)
#define			CUST_TP_INFO_ADDR			(flash_sector_calibration + CALIB_OFFSET_TP_INFO)
#define			CUST_RC32K_CAP_INFO_ADDR	(flash_sector_calibration + OFFSET_CUST_RC32K_CAP_INFO)
#endif
// 0x100 ~ 0x7ff reserve for sihui
#define         FLASH_ADR_STATIC_OOB	    (flash_sector_calibration + 0x800)
        #if (!PROVISION_FLOW_SIMPLE_EN)
#define         FLASH_ADR_DEV_UUID	    	(flash_sector_calibration + 0x810)
        #endif
#endif
#endif

enum{
	// send cmd part 
	HCI_GATEWAY_CMD_START		= 0x00,
	HCI_GATEWAY_CMD_STOP		= 0x01,
	HCI_GATEWAY_CMD_RESET       = 0x02,
	HCI_GATEWAY_CMD_CLEAR_NODE_INFO	=0x06,
	HCI_GATEWAY_CMD_SET_ADV_FILTER 	=0x08,
	HCI_GATEWAY_CMD_SET_PRO_PARA 	=0x09,
	HCI_GATEWAY_CMD_SET_NODE_PARA	=0x0a,
	HCI_GATEWAY_CMD_START_KEYBIND 	=0x0b,
	HCI_GATEWAY_CMD_GET_PRO_SELF_STS = 0x0c,
    HCI_GATEWAY_CMD_SET_DEV_KEY     = 0x0d,
    HCI_GATEWAY_CMD_GET_SNO         = 0x0e,
    HCI_GATEWAY_CMD_SET_SNO         = 0x0f,
    HCI_GATEWAY_CMD_GET_UUID_MAC        = 0x10,
    HCI_GATEWAY_CMD_DEL_VC_NODE_INFO    = 0x11,
    HCI_GATEWAY_CMD_SEND_VC_NODE_INFO	= 0x12,
    
	// rsp cmd part 
	HCI_GATEWAY_RSP_UNICAST	=0x80,
	HCI_GATEWAY_RSP_OP_CODE	=0X81,
	HCI_GATEWAY_KEY_BIND_RSP = 0x82,
	HCI_GATEWAY_CMD_STATIC_OOB_RSP = 0x87,// HCI send back the static oob information 
	HCI_GATEWAY_CMD_UPDATE_MAC	 = 0x88,
	HCI_GATEWAY_CMD_PROVISION_EVT = 0x89,
	HCI_GATEWAY_CMD_KEY_BIND_EVT = 0x8a,
	HCI_GATEWAY_CMD_PRO_STS_RSP = 0x8b,
	HCI_GATEWAY_CMD_SEND_ELE_CNT = 0x8c,
	HCI_GATEWAY_CMD_SEND_NODE_INFO = 0x8d,
	HCI_GATEWAY_CMD_SEND_CPS_INFO	= 0x8e,
	HCI_GATEWAY_CMD_HEARTBEAT	= 0x8f,
	HCI_GATEWAY_CMD_SEND_MESH_OTA_STS	= 0x98,
	HCI_GATEWAY_CMD_SEND_UUID   = 0x99,
	HCI_GATEWAY_CMD_SEND_IVI    = 0x9a,
	HCI_GATEWAY_CMD_SEND_SRC_CMD = 0x9c,
	HCI_GATEWAY_CMD_SEND_SNO_RSP    = 0xa0,
	HCI_GATEWAY_CMD_SEND       = 0xb1,
	HCI_GATEWAY_DEV_RSP         = 0xb2,
	HCI_GATEWAY_CMD_LINK_OPEN   = 0xb3,
	HCI_GATEWAY_CMD_LINK_CLS    =0xb4,
	HCI_GATEWAY_CMD_SEND_BACK_VC = 0xb5,
	HCI_GATEWAY_CMD_LOG_STRING	= 0xb6,
	HCI_GATEWAY_CMD_LOG_BUF		= 0xb7,
	
};
//---------hci_cmd_from_usb
enum{
	// 0xff00 -- 0xff7f for user
	HCI_CMD_USER_START			= 0xFF00,
	HCI_CMD_USER				= HCI_CMD_USER_START,
	HCI_CMD_USER_END			= 0xFF7F,
	HCI_CMD_TSCRIPT				= 0xFFA0,
	HCI_CMD_BULK_CMD2MODEL		= 0xFFA1,
	HCI_CMD_BULK_SET_PAR		= 0xFFA2,			// to VC node
	HCI_CMD_BULK_CMD2DEBUG		= 0xFFA3,
	HCI_CMD_ADV_PKT				= 0xFFA4,			// to bear and GATT
	HCI_CMD_ADV_DEBUG_MESH_DONGLE2BEAR	= 0xFFA5,	// only to bear
	HCI_CMD_ADV_DEBUG_MESH_DONGLE2GATT	= 0xFFA6,	// only to gatt
	HCI_CMD_ADV_DEBUG_MESH_LED	= 0xFFA7,			// control LED
	HCI_CMD_BULK_SET_PAR2USB	= 0xFFA8,
	HCI_CMD_SET_VC_PAR			= 0xFFAA,
	//
	HCI_CMD_KMA_DONGLE_SET_MAC  			= 0xFFE0,
	HCI_CMD_KMA_DONGLE_SPP_TEST_DATA		= 0xFFE1,
	HCI_CMD_KMA_DONGLE_SPP_TEST_STATUS  	= 0xFFE2,
	HCI_CMD_KMA_DONGLE_SET_ADV_REPORT_EN	= 0xFFE3,
	HCI_CMD_USER_DEFINE			= 0xFFE4,
	HCI_CMD_GATEWAY_CMD			= 0xFFE8,
	HCI_CMD_GATEWAY_CTL			= 0xFFE9,
	HCI_CMD_GATEWAY_OTA			= 0xFFEA,
	HCI_CMD_MESH_OTA			= 0xFFEB,
	//
	HCI_CMD_PROVISION			= 0xFEA0,
};
enum{
	MESH_OTA_SET_TYPE			= 1,//cmd for the mesh ota ctl part 
	MESH_OTA_ERASE_CTL			= 2,
};
#define HCI_CMD_LEN				(2)

#define HCI_CMD_LOW(cmd)		(cmd & 0xFF)
#define HCI_CMD_HIGH(cmd)		((cmd >> 8) & 0xFF)

enum{
    GATT_OTA_SUCCESS                    = 0,
    GATT_OTA_FW_SIZE_TOO_BIG            = 1,
    GATT_OTA_TIMEOUT_DISCONNECT         = 2,
    GATT_OTA_START                      = 3,
};

enum{
    OTA_REBOOT_FLAG                   	= 0,
};


extern u32 flash_sector_mac_address;
extern u32 flash_sector_calibration;

#if AUTO_ADAPT_MAC_ADDR_TO_FLASH_TYPE_EN
void blc_readFlashSize_autoConfigCustomFlashSector(void);
#else
#define blc_readFlashSize_autoConfigCustomFlashSector()     // null
#endif

#ifndef WIN32
#if(__TL_LIB_8258__ || (MCU_CORE_TYPE == MCU_CORE_8258))
#include "stack/ble/blt_config.h"
#elif(MCU_CORE_TYPE == MCU_CORE_8278)
#include "stack/ble_8278/blt_config.h"
#else
typedef struct{
	u8 conn_mark;
	u8 ext_crystal_en;
}misc_para_t;

misc_para_t blt_miscParam;
static inline void blc_app_setExternalCrystalCapEnable(u8  en)
{
	blt_miscParam.ext_crystal_en = en;
}

static inline void blc_app_loadCustomizedParameters(void)
{
	 if(!blt_miscParam.ext_crystal_en)
	 {
		 //customize freq_offset adjust cap value, if not customized, default ana_81 is 0xd0
		 if( (*(unsigned char*) (CUST_CAP_INFO_ADDR)) != 0xff ){
			 //ana_81<4:0> is cap value(0x00 - 0x1f)
			 analog_write(0x81, (analog_read(0x81)&0xe0) | ((*(unsigned char*) (CUST_CAP_INFO_ADDR))&0x1f) );
		 }else if( (*(unsigned char*) (0x76010)) != 0xff ){ // no 1M flash for 8269
			 analog_write(0x81, (analog_read(0x81)&0xe0) | ((*(unsigned char*) (0x76010))&0x1f) );
		 }
	 }


	 // customize TP0/TP1
	 if( ((*(unsigned char*) (CUST_TP_INFO_ADDR)) != 0xff) && ((*(unsigned char*) (CUST_TP_INFO_ADDR+1)) != 0xff) ){
		 rf_update_tp_value(*(unsigned char*) (CUST_TP_INFO_ADDR), *(unsigned char*) (CUST_TP_INFO_ADDR+1));
	 }else if( ((*(unsigned char*) (0x76011)) != 0xff) && ((*(unsigned char*) (0x76011+1)) != 0xff) ){
		 rf_update_tp_value(*(unsigned char*) (0x76011), *(unsigned char*) (0x76011+1)); // no 1M flash for 8269
	 }

	  //customize 32k RC cap, if not customized, default ana_32 is 0x80
	 if( (*(unsigned char*) (CUST_RC32K_CAP_INFO_ADDR)) != 0xff ){
		 //ana_81<4:0> is cap value(0x00 - 0x1f)
		 analog_write(0x32, *(unsigned char*) (CUST_RC32K_CAP_INFO_ADDR) );
	 }
}
#endif
#endif

/////////////////// Code Zise & Feature ////////////////////////////

#if ( __TL_LIB_8261__ || (MCU_CORE_TYPE == MCU_CORE_8261) )
	#define BLE_STACK_SIMPLIFY_4_SMALL_FLASH_ENABLE		1
	#define BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE		0
#endif


#ifndef BLE_STACK_SIMPLIFY_4_SMALL_FLASH_ENABLE
#define BLE_STACK_SIMPLIFY_4_SMALL_FLASH_ENABLE			0
#endif

//for 8261 128k flash
#if (BLE_STACK_SIMPLIFY_4_SMALL_FLASH_ENABLE)
	#define		BLS_ADV_INTERVAL_CHECK_ENABLE					0
#endif

#ifndef BLE_P256_PUBLIC_KEY_ENABLE
#define BLE_P256_PUBLIC_KEY_ENABLE								0
#endif

#ifndef BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE
#define BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE			1
#endif

//default ll_master_multi connection
#ifndef  LL_MASTER_SINGLE_CONNECTION
#define  LL_MASTER_SINGLE_CONNECTION					0
#endif

#ifndef  LL_MASTER_MULTI_CONNECTION
#define  LL_MASTER_MULTI_CONNECTION						0
#endif

//#if (LL_MASTER_SINGLE_CONNECTION )
//	#define  LL_MASTER_MULTI_CONNECTION					0
//#else
//	#define  LL_MASTER_MULTI_CONNECTION					1
//#endif

#if (BLE_MODULE_LIB_ENABLE || BLE_MODULE_APPLICATION_ENABLE)  //for ble module
	#define		BLS_DMA_DATA_LOSS_DETECT_AND_SOLVE_ENABLE		1
	#define		BLS_SEND_TLK_MODULE_EVENT_ENABLE				1
	#define		BLS_ADV_INTERVAL_CHECK_ENABLE					0
#endif

//when rf dma & uart dma work together
#ifndef		BLS_DMA_DATA_LOSS_DETECT_AND_SOLVE_ENABLE
#define		BLS_DMA_DATA_LOSS_DETECT_AND_SOLVE_ENABLE		0
#endif

#ifndef		BLS_SEND_TLK_MODULE_EVENT_ENABLE
#define 	BLS_SEND_TLK_MODULE_EVENT_ENABLE				0
#endif

#ifndef		BLS_ADV_INTERVAL_CHECK_ENABLE
#define		BLS_ADV_INTERVAL_CHECK_ENABLE					1
#endif

#if LIB_TELINK_MESH_SCAN_MODE_ENABLE
#define		BLS_TELINK_MESH_SCAN_MODE_ENABLE				1
#endif

/////////////////  scan mode config  //////////////////////////
#ifndef		BLS_TELINK_MESH_SCAN_MODE_ENABLE
#define		BLS_TELINK_MESH_SCAN_MODE_ENABLE				0
#endif

#if(BLS_TELINK_MESH_SCAN_MODE_ENABLE)
	#define		BLS_BT_STD_SCAN_MODE_ENABLE					0
#else
	#ifndef		BLS_BT_STD_SCAN_MODE_ENABLE
	#define		BLS_BT_STD_SCAN_MODE_ENABLE					1
	#endif
#endif




#ifndef BLE_LL_ADV_IN_MAINLOOP_ENABLE
#define BLE_LL_ADV_IN_MAINLOOP_ENABLE					1
#endif


#define FW_SIZE_MAX_K			    (FLASH_ADR_AREA_FIRMWARE_END / 1024) // 192  //192K

#define OTA_CMD_INTER_TIMEOUT_S		30
#define OTA_KMADONGLE_PAUSE_TIMEOUT_S   OTA_CMD_INTER_TIMEOUT_S

#ifndef PM_DEEPSLEEP_RETENTION_ENABLE
#define PM_DEEPSLEEP_RETENTION_ENABLE					0
#endif

#ifndef ONLINE_STATUS_EN
#define ONLINE_STATUS_EN					            0
#endif

#ifndef DUAL_MODE_ADAPT_EN
#define DUAL_MODE_ADAPT_EN					            0
#endif
#ifndef DUAL_MODE_WITH_TLK_MESH_EN
#define DUAL_MODE_WITH_TLK_MESH_EN					    0
#endif

///////////////////////////////////////dbg channels///////////////////////////////////////////
#ifndef	DBG_CHN0_TOGGLE
#define DBG_CHN0_TOGGLE
#endif

#ifndef	DBG_CHN0_HIGH
#define DBG_CHN0_HIGH
#endif

#ifndef	DBG_CHN0_LOW
#define DBG_CHN0_LOW
#endif

#ifndef	DBG_CHN1_TOGGLE
#define DBG_CHN1_TOGGLE
#endif

#ifndef	DBG_CHN1_HIGH
#define DBG_CHN1_HIGH
#endif

#ifndef	DBG_CHN1_LOW
#define DBG_CHN1_LOW
#endif

#ifndef	DBG_CHN2_TOGGLE
#define DBG_CHN2_TOGGLE
#endif

#ifndef	DBG_CHN2_HIGH
#define DBG_CHN2_HIGH
#endif

#ifndef	DBG_CHN2_LOW
#define DBG_CHN2_LOW
#endif

#ifndef	DBG_CHN3_TOGGLE
#define DBG_CHN3_TOGGLE
#endif

#ifndef	DBG_CHN3_HIGH
#define DBG_CHN3_HIGH
#endif

#ifndef	DBG_CHN3_LOW
#define DBG_CHN3_LOW
#endif

#ifndef	DBG_CHN4_TOGGLE
#define DBG_CHN4_TOGGLE
#endif

#ifndef	DBG_CHN4_HIGH
#define DBG_CHN4_HIGH
#endif

#ifndef	DBG_CHN4_LOW
#define DBG_CHN4_LOW
#endif

#ifndef	DBG_CHN5_TOGGLE
#define DBG_CHN5_TOGGLE
#endif

#ifndef	DBG_CHN5_HIGH
#define DBG_CHN5_HIGH
#endif

#ifndef	DBG_CHN5_LOW
#define DBG_CHN5_LOW
#endif


