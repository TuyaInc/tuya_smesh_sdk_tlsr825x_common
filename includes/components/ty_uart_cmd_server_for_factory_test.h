/*************************************************************************
	> File Name: ty_uart_cmd_server_for_factory_test.h
	> Author: 
	> Mail: 
	> Created Time: Thu 13 Jun 2019 19:47:00 CST
 ************************************************************************/

#ifndef _TY_UART_CMD_SERVER_FOR_FACTORY_TEST_H
#define _TY_UART_CMD_SERVER_FOR_FACTORY_TEST_H

#include "board.h"

#define BIT(n)                  		    (1<<(n))

//ONE FRAME
#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_HEAD1                     0x00
#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_HEAD2                     0x01
#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_HEAD3                     0x02
#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_CMD                       0x03
#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_LEN1                      0x04
#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_LEN2                      0x05
#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_DATA                      0x06

#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_MIN_LEN                   0x07
#define     F_UART_CMD_SERVER_FOR_FACTORY_TEST_MAX_LEN                   0xFF



//ty means app uart cmd
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_ENTER              0x00
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_QUERY_HID          0x01
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_GPIO_TEST          0x02
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_WRITE_AUTH_INFO    0x03
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_QUERY_INFO         0x04
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_RESET              0x05
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_QUERY_FINGERPRINT  0x06
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_WRITE_HID          0x07
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_RSSI_TEST          0x08
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_WRITE_OEM_INFO     0x09

#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_START_SUBC         0x0C
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_STOP_SUBC          0x0D
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_WRITE_COUNTRY_CODE    0x0E
#define      CMD_UART_CMD_SERVER_FOR_FACTORY_TEST_READ_COUNTRY_CODE     0x0F


//some import info
#define H_ID_LEN                    20
#define P_ID_LEN                    8
#define AUTH_KEY_LEN                32
#define UUID_LEN			        16
#define MAC_LEN                     12
#define FIRMNAME_MAX_LEN            60
#define FIRMVERSION_MAX_LEN         10

typedef enum{
    COUNTRY_CODE_CN = 0,
    COUNTRY_CODE_US = 1,
    COUNTRY_CODE_JP = 2,
    COUNTRY_CODE_EU = 3,
}country_code_t;

//初始化结构体
typedef struct{
    u8 is_need_fingerprint_check:1;
    u8 is_need_get_pid_from_cloud:1;
    u8 if_support_country_code:1;
    u8 if_support_gpio_test_num:1;

    u8 is_need_update_mac_in_flash:1;
    u32 mac_address;

//    u8 hid[H_ID_LEN];
//    u8 pid[P_ID_LEN];
//    u8 authkey[AUTH_KEY_LEN];
//    u8 uuid[UUID_LEN];
//    u8 mac[MAC_LEN];
    u8 firmname[FIRMNAME_MAX_LEN];//firm name string 
    u8 firmversion[FIRMVERSION_MAX_LEN];//firm version string
}ty_uart_cmd_server_for_factory_test_params_s;


//对外功能函数集合结构体
typedef struct{
    void (*init)(ty_uart_cmd_server_for_factory_test_params_s *param);//初始化
    void (*receive_cmd)(u8 cmd, u8 *para, u8 len);//接收处理命令
    void (*send_cmd)(u8 cmd, u8 *para, u8 len);//发送命令

    void (*set_enter_callback)(void (*cb)(void));//设置进入产测时的回调函数
    void (*set_gpio_test_callback)(u8 (*cb)(void));//设置GPIO测试的回调函数(cb 阻塞等回复:1-ok.0-false)
    void (*set_rssi_test_callback)(u8 (*cb)(void));//设置RSSI测试的回调函数(cb 阻塞等回复:0-false,> 0 |rssi|)
    void (*set_rssi_test_start_callback)(u8 (*cb)(void));//设置RSSI测试的回调函数(cb 阻塞等回复:0-false,> 0 |rssi|)
    void (*set_vendor_test_callback)(u8 (*cb)(void));//设置VENDOR测试的回调函数(cb 无需等待回复，cb中自己处理回复)
    void (*set_reset_callback)(void (*cb)(void));//设置reset时的回调函数
    void (*set_oem_config_msg_callback)(u8 (*cb)(u16 msg_len, u8 *msg));//设置oem config 回调，将产测工具发来的oem配置信息传送到该回调函数，在该回调函数内做oem的配置
}ty_uart_cmd_server_for_factory_test_s;


extern ty_uart_cmd_server_for_factory_test_s ty_uart_cmd_server_for_factory_test; 
u8 is_auth_by_tuya(void);


#endif
