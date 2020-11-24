/*************************************************************************
	> File Name: app_uart.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Feb 2019 22:29:34 CST
 ************************************************************************/
#include "app_uart.h"
#include "ty_fifo.h"
#include "ty_nv.h"
#include "ty_timer_event.h"
#include "base_oem_config.h"
#include "hal_uart.h"
#include "tuya_sigmesh_hal.h"

#define     F_HEAD1                     0x00
#define     F_HEAD2                     0x01
#define     F_HEAD3                     0x02
#define     F_CMD                       0x03
#define     F_LEN1                      0x04
#define     F_LEN2                      0x05
#define     F_DATA                      0x06

#define     F_MIN_LEN                   0x07
#define     F_MAX_LEN                   0xFF

static u8 uart_init_flg = 0;

static void uart_server_run(void);

inline static u8 check_sum(u8 *data,u8 len){
    u8 i,sum = 0;
    for(i=0;i<len;i++){
        sum+=data[i];
    }
    return sum;
}



////////////////////////////////////////////////////////////////////////////////////
//app_uart正文
////////////////////////////////////////////////////////////////////////////////////
//uint8_t get_if_uart_init(void){
//    return uart_init_flg;
//}

void app_uart_reinit(u32 baud){
    BAUD_TYPE_t _baud;
    switch(baud){
        case 115200:_baud = BAUD_RATE_115200;break;
        case 19200:_baud = BAUD_RATE_19200;break;
        default:_baud = BAUD_RATE_9600;break;
    }

#if CONFIG_LOG_ON
    #if (TY_BT_MODULE == TYBT8C)
        hal_uart_init(BAUD_RATE_115200, GPIO_UART1_TX, GPIO_UART1_RX);
    #else
        hal_uart_init(BAUD_RATE_115200, GPIO_UART0_TX, GPIO_UART0_RX);
    #endif
#else
    #if (TY_BT_MODULE == TYBT8C)
        hal_uart_init(_baud, GPIO_UART1_TX, GPIO_UART1_RX);
    #else
        hal_uart_init(_baud, GPIO_UART0_TX, GPIO_UART0_RX);
    #endif
#endif
}

void app_uart_deinit(void){
//    uart_init_flg = 0;
}

void app_uart_init(void){//除了串口初始化，还有 FIFO 初始化、存储初始化、广播初始化、产测初始化、与mcu通信初始化
//    uart_init_flg = 1;

    hal_flash_init();//空
    
    app_uart_reinit(9600);
    ty_fifo_init();

    app_unprov_beacon_init();//PID
    app_factory_test_init();
    app_mcu_protocol_init();
}
/****************************************************
是一个 loop 函数，不断执行从串口读取数据，放入 fifo 中
此外还有三个 loop 函数在这个总的 loop 中执行
app_mcu_protocol_run();
app_factory_test_run();
uart_server_run();//解析FIFO中的数据，并调用相应的处理函数
*********************************************************/
void app_uart_run(void){
    u8 buf[254];
    int len = hal_uart_read(buf,254);

    if(len > 0){
        ty_fifo_add(buf,len);
        PR_DEBUG("%-30s","RECEIVE RAW DATA:");
        for(u8 i=0;i<len;i++){
            PR_DEBUG_RAW("%02X ",buf[i]&0xFF); 
        }
        PR_DEBUG_RAW("\n");
    }

    app_mcu_protocol_run();
    app_factory_test_run();

    uart_server_run();//解析FIFO中的数据，并调用相应的处理函数
}

/*************************************************************************
按照串口协议解析 FIFO 中的串口数据，获取有效的数据帧，根据数据帧类别，分别送到：

产测数据处理接口 app_factory_test_cmd(cmd,&buf[F_DATA],len)
与 MCU 通信的串口对接数据处理接口 app_mcu_protocol_cmd(cmd,&buf[F_DATA],len)
*****************************************************************************/
static void uart_server_run(void){
    static u8 is_factory = 1;
    u8 i,num = ty_fifo_get_size();
    if(num < F_MIN_LEN)return;
    
    //1.judge head
    u8 buf[256];
    ty_fifo_read(buf,F_MIN_LEN);//get head length datas,judge if it's head
    if(((buf[F_HEAD1] != 0x66) || (buf[F_HEAD2] != 0xaa) || (buf[F_HEAD3] != 0x00)) &&//factory 
            ((buf[F_HEAD1] != 0x55) || (buf[F_HEAD2] != 0xaa) || (buf[F_HEAD3] != 0x00))){//mesh common
        ty_fifo_pop(1);
        return;
    }

    //2.judge if it's a whole frame
    u8 head = buf[F_HEAD1];
    u8 cmd = buf[F_CMD];
    u8 len = buf[F_LEN2];
    u8 total_len = len + F_MIN_LEN;
    if(len > F_MAX_LEN){//error frame,the max frame data len is pid+version=39
        ty_fifo_pop(3);
        return;
    }
    if(num < total_len)return;

    //3.judge check sum 
    ty_fifo_read(buf,total_len);//read all frame data
    u8 ck_sum = check_sum(buf,total_len-1);
    if(ck_sum == buf[total_len-1]){
        //LOG-FOR-DEBUG
        PR_DEBUG("%-30s","RECEIVE RAW DATA:");
        for(i=0;i<total_len;i++){
            PR_DEBUG_RAW("%02X ",buf[i]&0xFF); 
        }
        PR_DEBUG_RAW("\n");

        ty_fifo_pop(total_len);//correct frame,pop this frame length data
        if(head == 0x66){//产测
            if(get_if_factory_test_close()){
                return;
            }
            app_factory_test_cmd(cmd,&buf[F_DATA],len);
        }else if(head == 0x55){//mcu
            app_mcu_protocol_cmd(cmd,&buf[F_DATA],len);       
        }
    }else{//check sum not correct,pop the head length data
        ty_fifo_pop(3);
        return;     
    }
}


