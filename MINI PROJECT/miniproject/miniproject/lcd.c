//lcd.c
//lcd.h
#include <lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "lcd_defines.h"

void writeLCD(u32 byte)
{
	//select write operation
	IOCLR0=1<<LCD_RW;
	//writebyte to lcd datapins
	WRITEBYTE(IOPIN0,LCD_DATA,byte);
	//provide high to low pulse
	IOSET0=1<<LCD_EN;
	delayUs(1);
	IOCLR0=1<<LCD_EN;
	delayMs(2);
}
void cmdLCD(u32 cmdbyte)
{
	IOCLR0=1<<LCD_RS;
	writeLCD(cmdbyte);	
}
void Init_LCD(void)
{
	//cfg p0.8(d0) to p0.15(d7)
	//p0.16(rs), p0.17(rw), p0.18(en)
	IODIR0|=0xFF<<LCD_DATA;
	IODIR0|=1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
	//poweron delay
	delayMs(15);
	cmdLCD(0x30);
	delayMs(5);
	cmdLCD(0x30);
	delayUs(100);
	cmdLCD(0x30);
	cmdLCD(MODE_8BIT_2LINE);
	cmdLCD(DISP_ON_CUR_OFF);
	cmdLCD(CLEAR_LCD);
	cmdLCD(SHIFT_CUR_RIGHT);
}
void charLCD(u32 asciiVal)
{
	//set data reg
	IOSET0=1<<LCD_RS;
	//write ascii value via data reg to ddram
	writeLCD(asciiVal);
}
void strLCD(s8 *str)
{
	while(*str)
	charLCD(*str++);
}
void U32LCD(u32 n)
{
	s32 i=0;
	u32 a[10];
	if(n==0)
	{
		charLCD('0');
	}
	else
	{
		while(n>0)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
	for(--i;i>=0;i--)
	charLCD(a[i]);
	 }
}
void S32LCD(s32 num)
{
	if(num<0)
	{
		charLCD('-');
			num=-num;
	}
	U32LCD(num);
}
void F32LCD(f32 fnum,u32 ndp)
{
	u32 num,i;
	if(fnum<0.0)
	{
		charLCD('-');
		fnum=-fnum;
	}
	num=fnum;
	U32LCD(num);
	charLCD('.');
	for(i=0;i<ndp;i++)
	{
		fnum=(fnum-num)*10;
		num=fnum;
		charLCD(num+48);
	}
}
void Build_CGRAM(u8 *p,u8 nbytes)
{
	u32 i;
	//point to cgram
	cmdLCD(GOTO_CGRAM_START);
	//select data reg
	IOSET0=1<<LCD_RS;
	for(i=0;i<nbytes;i++)
	{
		//write to cgram via data reg
		writeLCD(p[i]); 
	}
	//point back to ddram start/display
	cmdLCD(GOTO_LINE1_POS0);
}
