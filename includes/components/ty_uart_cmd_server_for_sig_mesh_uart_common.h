/*************************************************************************
	> File Name: ty_uart_cmd_server_for_sig_mesh_uart_common.h
	> Author: 
	> Mail: 
	> Created Time: Wed 12 Jun 2019 17:08:28 CST
 ************************************************************************/

#ifndef _DRV_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_H
#define _DRV_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_H

#include "board.h"

//ONE FRAME
#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_HEAD1                     0x00
#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_HEAD2                     0x01
#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_HEAD3                     0x02
#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_CMD                       0x03
#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_LEN1                      0x04
#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_LEN2                      0x05
#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_DATA                      0x06

#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_MIN_LEN                   0x07
#define     F_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_MAX_LEN                   0xFF



#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_HEART                   0x00
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_QUERY_INFO              0x01
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_QUERY_WORK_MODE         0x02 
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_REPORT_STATE            0x03
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_RESET                   0x04
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_DOWNLOAD                0x06
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_UPLOAD                  0x07
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_QUERY_ALL               0x08
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_RSSI_TEST               0x0E
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_ENABLE_MESH_FUNC        0xB1
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_UPLOAD_AD               0xB2
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_GET_PUB_ADDRESS         0xB3
#define     CMD_TY_UART_CMD_SERVER_FOR_SIG_MESH_UART_COMMON_ENABLE_LOW_POWER        0xE5



typedef enum{
    LOW_POWER_DISABLE = 0x00,
    LOW_POWER_DEEP
}low_power_kind_e;

//初始化结构体
typedef struct{
}ty_uart_cmd_server_for_sig_mesh_uart_common_params_s;

//对外功能函数集合结构体
typedef struct{
    u8 (*init)(ty_uart_cmd_server_for_sig_mesh_uart_common_params_s *param);//初始化
    void (*receive_cmd)(u8 cmd, u8 *para, u8 len);//接收处理命令
    void (*send_cmd)(u8 cmd, u8 *para, u8 len);//发送命令
    void (*run)(void);//run放在loop中

    void (*set_work_state)(u8 state);//当工作状态有变化时调用该函数
    u8 (*get_work_state)(void);//获取工作状态
    void (*set_work_mode)(u8 mode);//设置工作模式
    u8 (*get_work_mode)(void);//获取工作模式
    void (*set_low_power_mode)(low_power_kind_e mode);//设置低功耗模式
    u8 (*get_low_power_mode)(void);//获取低功耗模式
    void (*set_mesh_local_control_mode)(u8 mode);//设置mesh本地控制模式
    u8 (*get_mesh_local_control_mode)(void);//获取mesh本地控制模式

    void (*set_mesh_local_control_pub_address)(u16 pub_addrss);//设置mesh本地联动的pub_address

    void (*set_query_info_callback)(u8 (*cb)(u8 *para, u8 len));//设置请求设备信息的回调函数(当MCU传来设备信息时会调用该回调函数，将参数返回到应用层)
    void (*set_reset_callback)(void (*cb)(void));//设置reset时的回调函数
    void (*set_rssi_test_callback)(u8 (*cb)(u8 is_start_or_stop));//设置RSSI测试的回调函数(cb：参数为1时为启动搜索，为0时为停止搜索，返回搜索结果回复:0-false,> 0 |rssi|)
    void (*set_ad_tx_callback)(void (*cb)(u16 adr_src, u16 adr_dst, u8 *params, u8 len, u8 is_use_params_adr));//设置ad_tx回调函数
}ty_uart_cmd_server_for_sig_mesh_uart_common_s;


extern ty_uart_cmd_server_for_sig_mesh_uart_common_s ty_uart_cmd_server_for_sig_mesh_uart_common;


#endif
