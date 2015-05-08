#include "device_1602.h"
#include "sys_51.h"

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
	dispstr(boot_str);
	delays(250);
	disp_painting();
}
//  0:W  1:R  2:M
//  0:'0' 1:'1' 2:'2'  3:'3'
// 
struct disp_info
{
	u8  S;
	u8  G;
	u8  str[14];
	u32  freq;
};

struct disp_info disp_info = {0};

void disp_up_freq(u32 freq)
{
	u8 buf[9];
	u8 i = 0;
	u8 quo;
	u8 k;
	u8 get_1 = 0;

	COMM_POS(0x44);
	for(k = 0; k < 14; k++ )
		dispch(" ");
	freq %= 1000000000;                //9
	quo = (u8)(freq / 100000000);      //8 
	if( quo != 0 ){
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

	quo = i % 3;
	get_1 = i / 3;

	for(i = 0; i < quo ; i++){
		disp_info.str[i] = buf[i];
	}
	disp_info.str[quo++] = '.';
	
	while(get_1--){
		for(k = 0; k < 3 ; k++){
			disp_info.str[quo++] = buf[i++];
		}
		disp_info.str[quo++] = '.';
	}
	quo--;
	disp_info.str[quo++] = 'H';
	disp_info.str[quo++] = 'z';
	disp_info.str[quo] = '\0';
	
	COMM_POS(0x44);
	dispstr(disp_info.str);
}

#define ASSERT()  do{\
		if(assert())\
			break;  \
	    delay(time) \
	    delay(time) \
	    delay(time) \
	    delay(time) \
		}while(0)
u8  wait_over( u8 (*assert)(void),u8 time)
{
	u8 i = 0;
	while( !assert()){
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
}
void enter_wait_status(u8 (*assert)(void))
{
    disp_info.S = 0;
	COMM_DISP(DISP_SCREEN_EN);
	COMM_POS(0x03);
	dispch('W');
	wait_over(assert,250);

}
void enter_Run_status( u8 (*assert)(void))
{
    disp_info.S = 1;
    COMM_DISP(DISP_SCREEN_EN);
	COMM_POS(0x03);
	dispch('R');
	wait_over(assert,1);
}
void  enter_mode( u8 (*assert)(void))
{
    disp_info.S = 2;
    u8 key_val = 0;
   	COMM_DISP(DISP_SCREEN_EN);
	COMM_POS(0x03);
	dispch('M');
    COMM_POS(0x09);
    COMM_DISP(DISP_SCREEN_EN | DISP_CUROS_EN | DISP_CUROS_GLITTER_EN);
    while(1){
	   	key_val = assert(); 
    	COMM_POS(0x09);
		dispch('0' + disp_info.G);
		if (ket_val==  KEY_MOD ){
			break;
		}
		if (key_val == KEY_UP){
			disp_info.G++;
			if(disp_info.G > 3){
				disp_info.G = 0;
			}			
		}
		if (key_val == KEY_DOWN){
			if(disp_info.G == 0){
				disp_info.G = 4 ;
			}			
			disp_info.G--;
		}
	}	
   	COMM_DISP(DISP_SCREEN_EN);
}











