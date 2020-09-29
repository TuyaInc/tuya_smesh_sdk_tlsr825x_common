/*************************************************************************
	> File Name: app_storage.c
	> Author: 
	> Mail: 
	> Created Time: Mon 03 Aug 2020 21:59:40 CST
 ************************************************************************/

#include "app_storage.h"


static u8 is_need_write;
static u8 storage_data[SAVE_UNIT8_SIZE];

inline u8 storage_data_updata(bool is_read){
    u8 buf[256];
    hal_flash_read_page(APP_STORAGE_ADRESS,256,buf);

    int i;
    for(i=SAVE_UNIT8_SIZE*SAVE_UNIT8_BACKUP_NUM;i>=0;i--){
        if(buf[i] != 0xFF)break;
    }

    if(((i+1)%SAVE_UNIT8_SIZE ==0) && (buf[i] == SAVE_FLAG)){
        if(is_read){
            memcpy(storage_data,&buf[i-SAVE_VALUE_SIZE],SAVE_UNIT8_SIZE);
            return i+1-SAVE_UNIT8_SIZE;
        }else{
            int left = SAVE_UNIT8_SIZE*SAVE_UNIT8_BACKUP_NUM-(i+1);
            if(left < SAVE_UNIT8_SIZE){
                hal_flash_erase_sector(APP_STORAGE_ADRESS);
                i = -1;
            }

            if(storage_data[SAVE_UNIT8_SIZE-1] == SAVE_FLAG)
                hal_flash_write_page(APP_STORAGE_ADRESS+i+1,SAVE_UNIT8_SIZE,storage_data);

            return 0;
        }
    }else{
        if(is_read){
            memset(storage_data,0xFF,SAVE_UNIT8_SIZE);
            storage_data[SAVE_VALUE_SIZE] = SAVE_FLAG;       
            return 0xFF;
        }else{
            hal_flash_erase_sector(APP_STORAGE_ADRESS);
            if(storage_data[SAVE_VALUE_SIZE] == SAVE_FLAG)
                hal_flash_write_page(APP_STORAGE_ADRESS,SAVE_UNIT8_SIZE,storage_data);
            
            return 0;
        }
    }

    return 0xFF;
}

int app_storage_init(void){
    is_need_write = 0;
    storage_data_updata(1);
}

int app_storage_read(u8 offset, u8 *pdata, u8 len){
    if(storage_data[SAVE_VALUE_SIZE] != SAVE_FLAG)
        return 0;
    if(offset >= SAVE_VALUE_SIZE)
        return 0;

    if((len+offset) > SAVE_VALUE_SIZE)
        len = SAVE_VALUE_SIZE - offset;
    memcpy(pdata,&storage_data[offset],len);
    return len;
}

int app_storage_save(u8 offset, u8 *pdata, u8 len){
    if(offset >= SAVE_VALUE_SIZE)
        return 0;
    if((len+offset) > SAVE_VALUE_SIZE)
        len = SAVE_VALUE_SIZE - offset;

    if(memcmp(pdata,&storage_data[offset],len) != 0){
        memcpy(&storage_data[offset],pdata,len);   

        is_need_write = 1;
        storage_data_updata(0);
    }
    return len;
}

