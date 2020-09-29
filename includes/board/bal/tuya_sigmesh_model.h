/*
 * tuya_sigmesh_model.h
 *
 *  Created on: 2020-05-28
 *      Author: Joey
 */

#ifndef _TUYA_SIGMESH_MODEL_H
#define _TUYA_SIGMESH_MODEL_H

//---TLSR special use---------------------------------------------

#define COMPANY_ID   (0x07D0)
#define VD_CID       (0xD007)

#define VD_TUYA_FSP_INFO_GET            0xC0
#define VD_TUYA_FSP_INFO_GET_STS        0xC1
#define VD_TUYA_FSP_ADDR_SET            0xC2
#define VD_TUYA_FSP_ADDR_SET_STS        0xC3
#define VD_TUYA_FSP_PROV_DATA_SET       0xC4
#define VD_TUYA_FSP_CONFIRM             0xC5
#define VD_TUYA_FSP_CONFIRM_STS         0xC6
#define VD_TUYA_FSP_COMPLETE            0xC7

#define VD_TUYA_WTITE           0xC9
#define VD_TUYA_WRITE_NOACK     0xCA
#define VD_TUYA_READ            0xCC
#define VD_TUYA_STATUS          0xCB
#define VD_TUYA_DATA            0xCD

//---user use---model_id------------------------------------------------------

#define TUYA_SIG_MD_G_ONOFF_S                0x1000
#define TUYA_SIG_MD_LIGHTNESS_S              0x1300
#define TUYA_SIG_MD_LIGHT_CTL_S              0x1303
#define TUYA_SIG_MD_LIGHT_CTL_TEMP_S         0x1306
#define TUYA_SIG_MD_LIGHT_HSL_S              0x1307
#define TUYA_VENDOR_MD_TUYA_S                0x000407D0

//---user use---opcode--------------------------------------------------------

#define TUYA_VD_TUYA_FSP_INFO_GET            ((VD_TUYA_FSP_INFO_GET << 16) | VD_CID)
#define TUYA_VD_TUYA_FSP_INFO_GET_STS        ((VD_TUYA_FSP_INFO_GET_STS << 16) | VD_CID)
#define TUYA_VD_TUYA_FSP_ADDR_SET            ((VD_TUYA_FSP_ADDR_SET << 16) | VD_CID)
#define TUYA_VD_TUYA_FSP_ADDR_SET_STS        ((VD_TUYA_FSP_ADDR_SET_STS << 16) | VD_CID)
#define TUYA_VD_TUYA_FSP_PROV_DATA_SET       ((VD_TUYA_FSP_PROV_DATA_SET << 16) | VD_CID)
#define TUYA_VD_TUYA_FSP_CONFIRM             ((VD_TUYA_FSP_CONFIRM << 16) | VD_CID)
#define TUYA_VD_TUYA_FSP_CONFIRM_STS         ((VD_TUYA_FSP_CONFIRM_STS << 16) | VD_CID)
#define TUYA_VD_TUYA_FSP_COMPLETE            ((VD_TUYA_FSP_COMPLETE << 16) | VD_CID)

#define TUYA_VD_TUYA_WTITE           ((VD_TUYA_WTITE << 16) | VD_CID)
#define TUYA_VD_TUYA_WRITE_NOACK     ((VD_TUYA_WRITE_NOACK << 16) | VD_CID)
#define TUYA_VD_TUYA_READ            ((VD_TUYA_READ << 16) | VD_CID)
#define TUYA_VD_TUYA_STATUS          ((VD_TUYA_STATUS << 16) | VD_CID)
#define TUYA_VD_TUYA_DATA            ((VD_TUYA_DATA << 16) | VD_CID)

#define TUYA_G_ONOFF_GET                    0x0182
#define TUYA_G_ONOFF_SET                    0x0282
#define TUYA_G_ONOFF_SET_NOACK              0x0382
#define TUYA_G_ONOFF_STATUS                 0x0482

#define TUYA_LIGHTNESS_GET                  0x4B82
#define TUYA_LIGHTNESS_SET                  0x4C82
#define TUYA_LIGHTNESS_SET_NOACK            0x4D82
#define TUYA_LIGHTNESS_STATUS               0x4E82

#define TUYA_LIGHT_CTL_GET                  0x5D82
#define TUYA_LIGHT_CTL_SET                  0x5E82
#define TUYA_LIGHT_CTL_SET_NOACK            0x5F82
#define TUYA_LIGHT_CTL_STATUS               0x6082

#define TUYA_LIGHT_CTL_TEMP_GET             0x6182
#define TUYA_LIGHT_CTL_TEMP_SET             0x6482
#define TUYA_LIGHT_CTL_TEMP_SET_NOACK       0x6582
#define TUYA_LIGHT_CTL_TEMP_STATUS          0x6682

#define TUYA_LIGHT_HSL_GET                  0x6D82
#define TUYA_LIGHT_HSL_SET                  0x7682
#define TUYA_LIGHT_HSL_SET_NOACK            0x7782
#define TUYA_LIGHT_HSL_STATUS               0x7882

typedef struct{
	unsigned char present;
	unsigned char target;
	unsigned char remain_t;
}ty_mesh_cmd_g_onoff_st_t;

typedef struct{
	unsigned char onoff;
	unsigned char tid;
	unsigned char transit_t;
	unsigned char delay;		// unit 5ms
}ty_mesh_cmd_g_onoff_set_t;


#endif
