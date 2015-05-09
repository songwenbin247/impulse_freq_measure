#include <reg52.h>
#include "sys_51.h"
#include "config.h"
#include "disp.h"
void key_init()
{
	
}



u8 read_key()
{
    u8 temp = 0;
	if(KEY1 || KEY2 || KEY3){
		if(KEY1){
			delay(250);
			return KEY1 ? VAL_MOD : VAL_NO;
		}
		if(KEY2){
			delay(250);
			if(KEY2){
				return disp_info.S == 'W' ? VAL_START : VAL_UP;
			}
			return VAL_NO;
		}
		if(KEY3){
			delay(250);
			return KEY2 ? VAL_DOWN : VAL_NO;
		}
	}
	return VAL_NO;
}

u8 key_assert(u32 count)
{
    u32 count = count;
	u8 val;
	u8 i;
	for(i = 0; i < 10; i++){
		if((val = read_key()) != VAL_NO){
		   return  KEY_OVER_COUNT | (val << 4);
		}
		delay(100);
	}
  return KEY_OVER_1S;
}


