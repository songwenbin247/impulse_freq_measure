#ifndef __DISP__H__
#define __DISP__H__
#include "config.h"
#include "sys_51.h"
extern struct disp_info disp_info;
void disp_boot();
void disp_up_freq(u8 *str);
u8 enter_wait_status(u8 (*assert)(u32),u32 count);
void enter_Run_status(u8 (*assert)(u32),u32 count);
void  enter_mode( u8 (*assert)(u32),u32 count);
#endif
