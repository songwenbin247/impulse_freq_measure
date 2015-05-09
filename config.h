#ifndef __CONFIG__H__
#define __CONFIG__H__
#include <reg52.h>

#define SYS_CLK       11592000
#define SYS_CLK_NUM_MS  11592
#define SYS_CLK_NUM_S   11592000
#define GRADE_N(grade) (SYS_CLK_NUM_MS * grade )

#define ASSERT_FREQ    5000000


#define GRADE0_MEASURE_MS  10
#define GRADE1_MEASURE_MS  100
#define GRADE2_MEASURE_MS  1000
#define GRADE3_MEASURE_MS  10000


#define OVER_COUNT      1
#define OVER_1S         2
#define OVER_NO         3

#define TIME_OVER_COUNT  OVER_COUNT
#define TIME_OVER_1S     OVER_1S
#define TIME_COUNTING    OVER_NO

#define KEY_OVER_COUNT  OVER_COUNT
#define KEY_OVER_1S     OVER_1S
#define KEY_COUNTING    OVER_NO

#define VAL_MOD        1
#define VAL_UP         2
#define VAL_DOWN       3
#define VAL_START      4
#define VAL_NO         0

#define 1602_PIN_4    P2^2
#define 1602_PIN_5    P2^1
#define 1602_PIN_6    P2^0
#define 1602_PIN_D    P0


#define KEY1       P2^3
#define KEY2       P2^5
#define KEY3       P2^7

#define KEY_MODE       KEY1
#define KEY_UP_START   KEY2
#define KEY_DOWN       KEY3

#define SELE_DIV   P1^6
#define CLK    T0
#define GATE   INT0
#define CON    P1^7


#endif
