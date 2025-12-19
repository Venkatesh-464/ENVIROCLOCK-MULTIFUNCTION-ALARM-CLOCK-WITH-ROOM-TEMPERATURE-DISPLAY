//mini_demo_2.c
#include  <LPC21xx.H>
#include "lcd_defines.h"
#include "lcd.h"
#include "rtc_defines.h"
#include "rtc.h"
#include "types.h"
#include "eint.h"
#include "kpm.h"
#include "menu.h"
#include "adc.h"

u32 alrm_hr,alrm_min,adcDval,alrm_flag,af;
u32 f;
f32 eAR;
#define ALRM_SW		4//p0.4			
#define ALRM_BUZZ  	5//p0.5
u8 cgramLUT[8]={0x04,0x04,0x0E,0x0E,0x1F,0x04,0x04,0x00};
main()
{
	s32 hour,min,sec,dayofweek,date,month,year;//i;
	Init_LCD();
	Init_RTC();
	Init_KPM();
	Init_INT();
	Init_ADC();
	IODIR0|=1<<ALRM_BUZZ;
	Build_CGRAM(cgramLUT,8);
	//SetRTCTimeInfo(4,8,2);
	//SetRTCDateInfo(24,10,2025);
	//SetRTCDay(5);
	while(1)
	{
		if(f==1)
		{
			f=0;
			displayMenu();
		}
		/*if(alrm_hr==HOUR && alrm_min==MIN)
		{
			Build_CGRAM(cgramLUT,8);
			if(af)
			{
				for(i=0;i<120000000;i++)
				{
					GetRTCTimeInfo(&hour,&min,&sec);
					DisplayRTCTime(hour,min,sec);
					IOSET0=1<<ALRM_BUZZ;
					cmdLCD(GOTO_LINE1_POS0+14);
					charLCD(0);
					if(((IOPIN0>>ALRM_SW)&1)==0)
						break;
				}
			//cmdLCD(GOTO_LINE1_POS0+13);
			//charLCD('Y');
			af=0;
			IOCLR0=1<<ALRM_BUZZ;
			cmdLCD(GOTO_LINE1_POS0+14);
			charLCD(' ');
		}
		}	*/
		IOCLR0=1<<ALRM_BUZZ;
		//cmdLCD(GOTO_LINE1_POS0+14);
		 //charLCD(' ');
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDay(&dayofweek);
		DisplayRTCDay(dayofweek);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		Read_ADC(1,&adcDval,&eAR);
		DisplayADC(eAR);
		if(alrm_flag)
		{
			cmdLCD(GOTO_LINE1_POS0+14);
			charLCD(0);
		}
		if(alrm_flag==0)
		{

				cmdLCD(GOTO_LINE1_POS0+14);
		 		charLCD(' ');
				
		}
		while(alrm_hr==HOUR && alrm_min==MIN && af)
		{
					GetRTCTimeInfo(&hour,&min,&sec);
					DisplayRTCTime(hour,min,sec);
					IOSET0=1<<ALRM_BUZZ;
					//cmdLCD(GOTO_LINE1_POS0+14);
					//charLCD(0);
					if(((IOPIN0>>ALRM_SW)&1)==0)
					{
						af=0;
						IOCLR0=1<<ALRM_BUZZ;
						//cmdLCD(GOTO_LINE1_POS0+14);
						//charLCD(' ');
					}
				alrm_flag=0;	
		}	
	}
}

