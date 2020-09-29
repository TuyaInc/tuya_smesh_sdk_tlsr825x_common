/*************************************************************************
	> File Name: ty_fifo.h
	> Author: 
	> Mail: 
	> Created Time: Thu 10 May 2018 04:50:21 PM CST
 ************************************************************************/

#ifndef _TY_FIFO_H
#define _TY_FIFO_H

#include "board.h"

#define ElementType u8 //存储数据元素的类型  

extern void ty_fifo_init(void);
extern u8 ty_fifo_isfull(void);
extern u8 ty_fifo_isempty(void);
extern u8 ty_fifo_clean(void);
extern u8 ty_fifo_get_size(void);
extern u8 ty_fifo_add_one(ElementType mdata);
extern u8 ty_fifo_add(ElementType *pdata,u8 len);
extern u8 ty_fifo_read(ElementType *pdata,u8 len);
extern u8 ty_fifo_pop(u8 len);

#endif
