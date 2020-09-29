/*************************************************************************
	> File Name: hal_log.h
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Jul 2019 22:05:09 CST
 ************************************************************************/

#ifndef _HAL_LOG_H
#define _HAL_LOG_H

#include "hal_sys.h"

void app_log_dump(uint8_t *title, uint8_t *buffer, uint16_t len);

#if CONFIG_LOG_ON
#define APP_LOG(format,...)  app_printf(format, ##__VA_ARGS__)
#define APP_LOG_DUMP(title, buffer, len)  app_log_dump(title, buffer, len)
#else
#define APP_LOG(format,...)
#define APP_LOG_DUMP(title, buffer, len)
#endif


#if 0
#define PR_DEBUG(_fmt_, ...) \
        app_printf("[dbg]%-30s:%d "_fmt_,__FUNCTION__,__LINE__,##__VA_ARGS__)
#define PR_DEBUG_RAW(_fmt_, ...) \
        app_printf(_fmt_,##__VA_ARGS__)
#define PR_DEBUG_HEX_ARRAY(array,len) do{ \
    if((len) == 0)break; \
    app_printf("%02X",(array)[0]); \
    for(u8 i=1;i<(len);i++){\
        app_printf(" %02X",(array)[i]); \
    } \
}while(0)

#else
#define PR_DEBUG(...)
#define PR_DEBUG_RAW(_fmt_, ...)
#define PR_DEBUG_HEX_ARRAY(data,len)
#endif



#endif
