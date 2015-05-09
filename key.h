#ifndef _KTY__H__
#define _KTY__H__
#include "config.h"
#define SET_DIV_FREQ(bool_val) SELE_DIV = val 
#define FREQ_DIV_2  0
#define FREQ_DIV_1  1

void key_init();
u8 read_key();
u8 key_assert(u32 count);

#endif
