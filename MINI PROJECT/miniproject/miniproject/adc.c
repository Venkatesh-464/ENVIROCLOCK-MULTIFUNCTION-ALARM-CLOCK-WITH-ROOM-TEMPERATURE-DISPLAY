//adc.c
#include<LPC21xx.h>
#include"types.h"
#include"delay.h"
#include"pin_function_defines.h"
#include"pin_connect_block.h"
#include"adc_defines.h"
#include "lcd.h"
#include "lcd_defines.h"

void Init_ADC(void)
{
	//cfg ADCR sfr
	ADCR=(1<<PDN_BIT )|(CCLKDIV<<CCLK_DIV_BIT);
	//cfg p0.27 pin as analog input pin
	cfgPortPinFunc(0,27,PIN_FUNC2);
}
void Read_ADC(u32 chNo,u32 *adcDval,f32 *eAR)
{
	//clear any previous chaannel selection
	ADCR&=0xFFFFFF00;
	//update required channel select
	//start anolg sampling and conversion
	ADCR|=1<<chNo|1<<ADC_START_BIT;
	delayUs(3);
	while(((ADDR>>DONE_BIT)&1)==0);
		ADCR&=~(1<<ADC_START_BIT);
		*adcDval=(ADDR>>RESULT_BIT)&1023;
		*eAR=(*adcDval*(3.3/1023));
}
void DisplayADC(f32 eAR)
{
//	u32 temp;
	//temp=eAR*100;
	cmdLCD(GOTO_LINE2_POS0+9);
	strLCD("T:");
	cmdLCD(GOTO_LINE2_POS0+11);
	U32LCD(eAR*100);
	charLCD(223);
	charLCD('C');
	charLCD(' ');
}
