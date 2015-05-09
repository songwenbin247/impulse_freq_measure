#include <reg52.h>
#include  "disp.h"
#include  "time.h"
#include  "key.h"
#include "config.h"

void main()
{
    u8 val;
	u32 freq;
	u32 freq1;
	key_init();
	time_init();
	disp_boot();
	while(1){
		while(1){
			val = enter_wait_status(key_assert,0);
			if(val == VAL_START){
				break;
			}
			enter_mode_status(key_assert,0);
		}
		measure_start();
		enter_Run_status(assert_measure,GRADE_N(disp_info.g_time));
		freq = measure_close(); 
		if (freq > ASSERT_FREQ){
			SET_DIV_FREQ(FREQ_DIV_2);
			measure_start();
			enter_Run_status(assert_measure,GRADE_N(disp_info.g_time));
			freq = measure_close(); 
			SET_DIV_FREQ(FREQ_DIV_1);
		}
		tran_freq_to_str(freq);
		disp_up_freq();
	}
	
}

