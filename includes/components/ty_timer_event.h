/*************************************************************************
	> File Name: ty_timer_event.h
	> Author: 
	> Mail: 
	> Created Time: Wed 10 Apr 2019 14:19:07 CST
 ************************************************************************/

#ifndef _TY_TIMER_EVENT_H
#define _TY_TIMER_EVENT_H

#include "board.h"

#define MAX_TY_TIMER_EVENT_NUM 6 

//ret 
// < 0 will delete the timer
// = 0 loop
// > 0 reset the interval_us
typedef int (*ty_timer_event_callback_t)(void);

typedef struct {
    ty_timer_event_callback_t  cb;
    u32                         t;
    u32                         interval;
}ty_timer_event_s;

// timer table managemnt
typedef struct {
    ty_timer_event_s           timer[MAX_TY_TIMER_EVENT_NUM];
    u8                          num;
}ty_timer_event_array_s;


extern void ty_timer_event_init(void);
extern void ty_timer_event_run(void);

extern int ty_timer_event_add(ty_timer_event_callback_t cb, u32 interval_us);
extern int ty_timer_event_delete(ty_timer_event_callback_t cb);

#endif
