#ifndef __TIME_H__
#define __TIME_H__

#include "sys_51.h"
#include "config.h"

void time_init();

u8 assert_measure(u32 count);
u32 measure_start();
u32 measure_close();
void  tran_freq_to_str(u32 freq);

#endif

