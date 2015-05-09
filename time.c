#include <reg52.h>
#include "sys_51.h"
#define TIME_IRQ_EN() EA = 1;\
					  ET0 = 1;\
					  ET1 = 1
#define TIME_START() TCON |= 0x50;\
					 CON = 1
#define TIME_MODE()	 TMOD = 0xD9
#define TIME_CLOSE() TCOM &= ~0x50
u16 sys_clk_num = 0;
u16 ext_clk_num = 0;
void time_init()
{
	TIME_IRQ_EN();
    SET_DIV_FREQ(FREQ_DIV_1);
    TIME_MODE();
}
void time0(void) interrupt 1
{
	ext_clk_num++;
}
void time1(void) interrupt 3
{
	sys_clk_num++;
}
u32 tem ;
u8 assert_measure(u32 count)
{
	u32 temp = 0;
	temp = (sys_clk_num << 16) + (TH1 << 8) + TH0 ;
	if( temp  >  count ){
		return TIME_OVER_COUNT;
	}
	if(temp - tem > SYS_CLK_NUM_S){
		tem = temp;
		return TIME_OVER_1S;
	}
	return TIME_COUNTING;
    
}

void measure_start()
{
	ext_clk_num = 0;
	sys_clk_num = 0;
	TIME_START();
	tem = SYS_CLK_NUM_S;
}


u32 measure_close()
{
	u32 sys_num = 0;
	u32 ext_num = 0;
    u64 temp = 0;
	CON = 0;
	delays(1);
	TIME_CLOSE();
	sys_clk_num = (sys_clk_num << 16) + (TH1 << 8) + TH0 ;
    ext_clk_num  = (sys_clk_num << 16) + (TH1 << 8) + TH0 ;
    temp = sys_clk_num << 32 ;
	temp /= SYS_CLK_NUM_MS;
	return (u32) (((ext_clk_num << 32)/ temp) & 0xFFFFFFFF);
}


void  tran_freq_to_str(u32 freq)
{
	u8 buf[13];
	u8 i = 0;
	u8 quo;
	u8 k;
	u8 get_1 = 0;

	freq %= 1000000000000;                   //12
	quo = (u8)(freq / 100000000000);         //11 
	if( quo != 0 ){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 100000000000;                       //11 
	quo = (u8)(freq / 10000000000);             //10
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 10000000000;                       //10
	quo = (u8)(freq / 1000000000);             //9
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 1000000000;                       //9 
	quo = (u8)(freq / 100000000);             //8
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	freq %= 100000000;                 //8 
	quo = (u8)(freq / 10000000);        //7
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 10000000;                  //7
	quo = (u8)(freq / 1000000);         //6
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 1000000;
	quo = (u8)(freq / 100000);
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 100000;
	quo = (u8)(freq / 10000);
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 10000;
	quo = (u8)(freq / 1000);
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 1000;
	quo = (u8)(freq / 100);
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	buf[i++] = '.';                  //  insert '.' 
	
	freq %= 100;
	quo = (u8)(freq / 10);
	if(get_1 == 1 || quo != 0){
		buf[i++] = quo + '0';
		get_1 = 1;
	}
	
	freq %= 10;
	if( quo != 0 ){
		buf[i++] = quo + '0';
	}

   quo = i < 10 ? i : 10;

   for(k = 0; k < quo; k++){
      disp_info.str[k] = buf[k];
   }
   if(disp_info.str[k - 1] == '.'){
      k--;
   }

	disp_info.str[k++] = 'H';
	disp_info.str[k++] = 'z';
	disp_info.str[k] = '\0';
	
}

