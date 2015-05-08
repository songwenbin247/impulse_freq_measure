#ifndef __DEVICE_1602_H__
#define __DEVICE_1602_H__

#include "reg52.h"
#include "sys_51.h"
#include "config.h"

#define PIN_4 
#define PIN_5
#define PIN_6
#define PIN_D_0_7

#define D_REG 0x01
#define C_REG 0x00
#define RS(arg)  PIN_4 = (bit)arg 

#define R_SELE 0x01
#define W_SELE 0x00
#define RW(arg) PIN_5 =(bit)arg

#define M_L 0x00
#define M_H 0x01
#define EN(arg)   PIN_6 = (bit)arg


#define GDATA() (PIN_D_0_7) 
#define SDATA(dat) PIN_D_0_7 = (dat)

#define COMM_CLEAR()   \
	write_cmd(0x01)

#define COMM_CURSOR_BACK() \
	write_cmd(0x02)


#define SHIFT_CUROS_RIGHT  (0x01 << 2)
#define SHIFT_CUROS_LEFT   0x00
#define SHIFT_WITH_SUROS 0x01
#define SHIFT_NOWITH_SUROS 0x00
#define COMM_SHIFT_WAY(curos_shift,char_shift) \
	write_cmd(0x04 | couros_shift | char_shift )


#define DISP_SCREEN_EN (0x01 << 3)
#define DISP_SCREEN_DIS (0x00)
#define DISP_CUROS_EN (0x01 << 2)
#define DISP_CUROS_DIS (0x00)
#define DISP_CUROS_GLITTER_EN (0x01)
#define DISP_CUROS_GLITTER_DIS (0x00)

#define COMM_DISP(D,C,B ) \
	write_cmd(0x08 | D  | C | B )

#define COMM_POS(pos)\
	write_cmd(0x80 | pos)

#define SYS_BUS_WIDE_4  (0x01 << 4)
#define SYS_BUS_WIDE_8  (0x00)
#define SYS_LINE_2 (0x01 << 3)
#define SYS_LINE_1 (0x00)
#define SYS_PIXELS_5_7 (0x00)
#define SYS_PIXELS_5_10 (0x01 << 2)

#define COMM_SYS_SET(DL,N,F) \
	write_cmd(0x20 | DL | N | F)

#define COMM_WRITE_DAT (dat) \
	write_dat(dat);

#define DELAY() \
			_nop_();\
			_nop_();\
			_nop_();\
			_nop_()

void delay(u8 ms);
u8 is_busy();
void write_cmd(u8 cmd);
void set_pos(u8 pos);
void write_dat(u8 dat);
void dispstr(u8 *s);
#define dispch(ch)  write_dat(ch)
void init_1602(u8 sys_bus_wide,
		  u8 sys_line,
		  u8 sys_pixels,
		  u8 disp_screen_sw,
		  u8 disp_curos_sw,
		  u8 disp_curos_glitter_sw,
		  u8 shift_curos_way,
		  u8 shift_char_way
		);

#endif
























