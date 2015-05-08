#ifndef __CONFIG__H__
#define __CONFIG__H__
#include <reg52.h>
#define 1602_PIN_4    P2^2
#define 1602_PIN_5    P2^1
#define 1602_PIN_6    P2^0
#define 1602_PIN_D    P0


#define Key1   P2^3
#define Key2   P2^5
#define Key3   P2^7

#define SELE   P1^6
#define CLK    T0
#define GATE   INT0
#define CON    P1^7


#endif
