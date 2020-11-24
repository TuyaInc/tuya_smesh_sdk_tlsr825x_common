/*************************************************************************
	> File Name: ty_uart_cmd_server_for_sig_mesh_uart_common_storage.h
	> Author: 
	> Mail: 
	> Created Time: Mon 03 Aug 2020 21:59:45 CST
 ************************************************************************/

#ifndef _APP_STORAGE_H
#define _APP_STORAGE_H

#include "board.h"

//4K
#define APP_STORAGE_ADRESS 0x7C000

#define SAVE_UNIT8_SIZE 8
#define SAVE_VALUE_SIZE 7 //SAVE_UNIT8_SIZE-1
#define SAVE_UNIT8_BACKUP_NUM 30






extern int app_storage_init(void);
extern int app_storage_read(u8 offset, u8 *pdata, u8 len);
extern int app_storage_save(u8 offset, u8 *pdata, u8 len);




#endif
