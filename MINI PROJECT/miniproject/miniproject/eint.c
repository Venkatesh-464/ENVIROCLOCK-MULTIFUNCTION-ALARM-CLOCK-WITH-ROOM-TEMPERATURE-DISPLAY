//eint.c
#include <LPC21xx.H>
#include "types.h"
#include "pin_function_defines.h"
#include "pin_connect_block.h"
#include "eint.h"
#include "delay.h"
#define LED1 	5
#define LED2  	6
extern u32 left_flag,right_flag;
void Init_INT(void)
{
	cfgPortPinFunc(0,1,EINT0_0_1);
	cfgPortPinFunc(0,3,EINT1_0_3);
	VICIntEnable|=1<<EINT0_VIC_CHN0|1<<EINT1_VIC_CHN0;
	VICVectCntl0=(1<<5)|EINT0_VIC_CHN0;
	VICVectCntl1=(1<<5)|EINT1_VIC_CHN0;
	VICVectAddr0=(u32)eint0_isr;
	VICVectAddr1=(u32)eint1_isr;
	EXTMODE=1<<0|1<<1;
}
void eint1_isr(void) __irq
{
	right_flag=1;
	IOSET0=1<<LED1;
	delayS(1);
	IOCLR0=1<<LED1;
	delayS(1);
	EXTINT=1<<1;
	VICVectAddr=0;
	//while(1);
}
void eint0_isr(void) __irq
{
	left_flag=1;
	IOSET0=1<<LED2;
	delayS(1);
	IOCLR0=1<<LED2;
	delayS(1);
	EXTINT=1<<0;
	VICVectAddr=0;
	//while(1);
}

