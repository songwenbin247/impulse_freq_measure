#include <reg52.h>
#include "sys_51.h"

void delay(u8 ms)
{
	u8 i;
	while(ms--){
		for(i = 0; i < 250; i++ ){
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
	}
}
void delays(u8 s)
{
	u8 i = 0;
	for(i = 0; i < s; i++){
		delay(250);
		delay(250);
		delay(250);
		delay(250);	
	}
}

#define EA (0x01 << 7)
#define 




void sys_init()
{
	PCON2 = 0x00;

}

void time_irq_init()
{
	EA = 1;
	ET1 = 1;
	ET2 = 1;
}
void time0_init()
{
	
}

	
