#include <intrins.h>
#include <reg52.h>
#include "device_1602.h"


void delay(unsigned char ms)
{
	unsigned char i;
	while(ms--){
		for(i = 0; i < 250; i++ ){
			_nop_();
			_nop_();
			_nop_();
			_nop_();
		}
	}
}

unsigned char is_busy()
{
	unsigned char result = 0;
	RS(C_REG);
	WR(R_SELE);
	EN(M_H);
	DELAY();
	result = GDATA() & 0x80;
	EN(M_L);
	return result;
}

void write_cmd(unsigned char cmd)
{
	while(is_busy());
	RS(C_REG);
	RW(W_SELE);
	EN(M_L);
	DELAY();
	SDATA(cmd);
	DELAY();
	EN(M_H);
	DELAY();
	EN(M_L);
}

void write_dat(unsigned char dat)
{
	while(is_busy());
	RS(D_REG);
	RW(W_SELE);
	EN(M_L);
	SDATA(dat);
	DELAY();
	EN(M_H);
	DELAY();
	EN(M_L);
}
/***********************************/
// input: 
// sys_bus_wide :   
//       SYS_BUS_WIDE_4 
//       SYS_BUS_WIDE_8
// sys_line :
//       SYS_LINE_2 
//       SYS_LINE_1
// sys_pixels :
//       SYS_PIXELS_5_7 
//       SYS_PIXELS_5_10 
// disp_screen_sw :
//       DISP_SCREEN_EN 
//       DISP_SCREEN_DIS
// disp_curos_sw :
//       DISP_CUROS_EN 
//       DISP_CUROS_DIS
// disp_curos_glitter_sw :
//       DISP_CUROS_GLITTER_EN 
//       DISP_CUROS_GLITTER_DIS
// shift_curos_way :
//       SHIFT_CUROS_RIGHT 
//       SHIFT_CUROS_LEFT  
// shift_char_way :
//       SHIFT_WITH_SUROS 
//       SHIFT_NOWITH_SUROS 
/***********************************/
void init_1602(unsigned char sys_bus_wide,
		  unsigned char sys_line,
		  unsigned char sys_pixels,
		  unsigned char disp_screen_sw,
		  unsigned char disp_curos_sw,
		  unsigned char disp_curos_glitter_sw,
		  unsigned char shift_curos_way,
		  unsigned char shift_char_way
		)
{
   COMM_SYS_SET(sys_bus_wide | sys_line | sys_pixels);
   delay(1);
   COMM_DISP(disp_screen_sw | disp_curos_sw | disp_curos_glitter_sw);
   delay(1);
   COMM_SHIFT_WAY(shift_curos_way | shift_char_way );_
   delay(1);
}

void dispstr(unsigned char *s)
{
	if(*s != '\0'){
		write_dat(*s);
		s++;
	}
}




