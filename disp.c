#include "device_1602.h"
#include "sys_51.h"
#include "disp.h"
//           ******************   
//           *S:R  | G:0      *         
//           *R:238674Hz      *
//           ******************   
//   S --> status :  
//      R: Running
//      W: Waiting for start 
//      M: Set the accuracy grade
//   G --> grade :
//      0: grade 0
//      1: grade 1
//      2: grade 2 
//      3: grede 3
//   R --> result :
//      Unit Hz 


//disp buff address 
//   00 01 02 ...
//   40 41 42 ...

static void disp_painting()
{
	COMM_CLEAR();
	dispstr("S:W   | G:0");
	COMM_POS(42);
	dispstr("R:0Hz");
}
u8 boot_str[] = "Welcome...";

struct disp_info
{
	u8   S;
	u8   G;
	u16  g_time;
	u8   str[13];
	u32  freq;
};

struct disp_info disp_info = {0};
void disp_boot()
{
	init_1602(SYS_BUS_WIDE_8,
			  SYS_LINE_1,
			  SYS_PIXELS_5_7,
			  DISP_SCREEN_EN,
			  DISP_CUROS_DIS,
			  DISP_CUROS_GLITTER_DIS,
              SHIFT_CUROS_RIGHT,
			  SHIFT_NOWITH_SUROS
			);	
	disp_info.S = 'W';
	disp_info.G = 0;
	disp_info.g_time = GRADE0_MEASURE_MS;
	disp_info.freq = 0;
	dispstr(boot_str);
	delays(250);
	disp_painting();
}
//  0:W  1:R  2:M
//  0:1000 1:'1' 2:'2'  3:'3'
// 

void disp_up_freq(u8 *str)
{
	u8 k;
	COMM_POS(0x44);
	for(k = 0; k < 14; k++ )
		dispch(" ");
	
	COMM_POS(0x44);
	dispstr(str);
}

#define ASSERT()   while(1){\
	               		res = assert(count); \
					    if(res & 0x0F == OVER_COUNT )\
							return (res & 0xF0) >> 4 ; \
						else if(res & 0x0F  == OVER_1S)
							break;
					}

u8  wait_over( u8 (*assert)(u32 count),u32 count)
{
	u8 res = 0;
	while(1)
		COMM_POS(0x04);
		disch('.');
		ASSERT();
		disch('.');
		ASSERT();
		disch('.');
		ASSERT();
		COMM_POS(0x04);
		dispstr("   ");
		ASSERT();
	}
    return 0;
}
u8  enter_wait_status(u8 (*assert)(u32),u32 count)
{
    u8 val;
	disp_info.S = 'W';
	COMM_DISP(DISP_SCREEN_EN);
	COMM_POS(0x03);
	dispch('W');
	while(1){
	  val = wait_over(assert,count);
	   if(val == VAL_MOD || val == VAL_START){
	   	return val;
	   }
	}
}

void enter_Run_status(u8 (*assert)(u32),u32 count)
{
    disp_info.S = 'R';
    COMM_DISP(DISP_SCREEN_EN);
	COMM_POS(0x03);
	dispch('R');
	wait_over(assert,count);
}
/***************************/
//
//    assert:
//        count --> no used
//       return:
//            VAL_MOD  | OVER_COUNT 
//            VAL_UP   | OVER_COUNT 
//            VAL_DOWN | OVER_COUNT 
//            VAL_XX   | OVER_1S
//            VAL_XX   | OVER_NO
/***************************/
void  enter_mode_status( u8 (*assert)(u32),u32 count)
{
    disp_info.S = 'M';
    u8 key_val = 0;
   	COMM_DISP(DISP_SCREEN_EN);
	COMM_POS(0x03);
	dispch('M');
    COMM_POS(0x09);
    COMM_DISP(DISP_SCREEN_EN | DISP_CUROS_EN | DISP_CUROS_GLITTER_EN);
    while(1){
	   	key_val = wait_over(count); 
		if (ket_val==  VAL_MOD ){
			break;
		}
		if (key_val == VAL_UP){
			disp_info.G++;
			if(disp_info.G > 3){
				disp_info.G = 0;
			}			
		}
		if (key_val == VAL_DOWN){
			if(disp_info.G == 0){
				disp_info.G = 4 ;
			}			
			disp_info.G--;
		}
		if(disp_info.G == 0)
			disp_info.g_time = GRADE0_MEASURE_MS;
		else if(disp_info.G == 1)
			disp_info.g_time = GRADE1_MEASURE_MS;
		else if(disp_info.G == 2)
			disp_info.g_time = GRADE2_MEASURE_MS;
		else
			disp_info.g_time = GRADE3_MEASURE_MS;
    
		COMM_POS(0x09);
		dispch('0' + disp_info.G);
	}	
   	COMM_DISP(DISP_SCREEN_EN);
}











