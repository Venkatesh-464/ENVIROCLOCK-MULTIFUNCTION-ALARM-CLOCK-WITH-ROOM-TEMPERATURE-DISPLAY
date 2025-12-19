#include <LPC21xx.H>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"

u32 g_key;
extern int alrm_hr,alrm_min,alrm_flag,af;

void Case_1_Call()
{
	loop:while(1)
		{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("1.H 2.M 3.S 4.W");
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("5.D 6.m 7.Y 8.E");
			g_key=KeyScan();
			while(ColScan()==0);
			delayMs(100);
			if((g_key<=8) && (g_key!=0))
				break;
			else
			{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Invalid");
				delayS(1);
				goto loop;
			}
		}	
}
void Case_2_Call()
{
	loop:while(1)
	{
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("Set Alarm");
		cmdLCD(GOTO_LINE2_POS0);
		strLCD("1.H 2.M 3.Exit");
		g_key=KeyScan();
		while(ColScan()==0);
		delayMs(100);
		if((g_key>3) || (g_key==0))
		{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("Invalid");
			delayS(1);
			goto loop;
		}
		else
			break;
	}
}
void Set_RTC_Info_Call()
{
	u8 key;
	u32 test,hour,min,sec,dayofweek,date,month,year;
	loop:switch(g_key)
	{
		case 1:	while(1)
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Enter hour(0-23)");
				cmdLCD(GOTO_LINE2_POS0);
				strLCD("HH");
				Read_Num(&hour,&key,&test);
				if(test)
						break;
				}
				if(hour>23 || test==2)
				{
					cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Invalid");
					delayS(1);
					goto loop;
				}
				else
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Data Saved");
				delayS(1);
				HOUR=hour;
				break;
				}
		case 2:	while(1)
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Enter Min(0-59)");
				cmdLCD(GOTO_LINE2_POS0);
				strLCD("MM");
				Read_Num(&min,&key,&test);
				if(test)
					break;
				}
				if(min>59 ||test==2)
				{
					cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Invalid");
					delayS(1);
					goto loop;
				}
				else
				{
					cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Data Saved");
					delayS(1);
					MIN=min;
					break;
				}
		case 3:	while(1)
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Enter Sec(0-59)");
				cmdLCD(GOTO_LINE2_POS0);
				strLCD("HH");
				Read_Num(&sec,&key,&test);
				if(test)
					break;
				}
				if(sec>59 || test==2)
				{
					cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Invalid");
					delayS(1);
					goto loop;
				}
				else
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Data Saved");
				delayS(1);
				SEC=sec;
				break;
				}
		case 4:	while(1)
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Enter DayofWeek");
				cmdLCD(GOTO_LINE2_POS0);
				strLCD("D");
				Read_Num(&dayofweek,&key,&test);
				if(test)
					break;
				}
				if(dayofweek>6 || test==2)
				{
					cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Invalid");
					delayS(1);
					goto loop;
				}
				else
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Data Saved");
				delayS(1);
				DOW=dayofweek;
				break;
				}
		case 5:	while(1)
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Enter Date(1-31)");
				cmdLCD(GOTO_LINE2_POS0);
				strLCD("DD");
				Read_Num(&date,&key,&test);
				if(test)
					break;
				}
				if(date>31|| date==0 || test==2)
				{
					cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Invalid");
					delayS(1);
					goto loop;
				}
				else
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Data Saved");
				delayS(1);
				DOM=date;
				break;
				}
		case 6:	while(1)
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Enter MonTH:1-12");
				cmdLCD(GOTO_LINE2_POS0);
				strLCD("MM");
				Read_Num(&month,&key,&test);
				if(test)
					break;
				}
				if(month>12 || month==0 || test==2)
				{
					cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Invalid");
					delayS(1);
					goto loop;
				}
				else
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Data Saved");
				delayS(1);
				MONTH=month;
				break;
				}
		case 7:	while(1)
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Enter Year");
				//cmdLCD(GOTO_LINE2_POS0);
				//strLCD("YYYY");
				Read_Num_Year(&year,&key,&test);
				if(year<2024 || test==2)
				{
					cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Invalid");
					delayS(1);
					goto loop;
				}
				else
				{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Data Saved");
				delayS(1);
				YEAR=year;
				break;
				}
		case 8:break;
		}
	}
}
void Set_Alarm_Call()
{	
	u8 key;
	u32 hour,min,test;
	loop:while(1)
	{
		if(g_key==1)
		{
			while(1)
			{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("Set Alarm Hour");
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("HH");
			Read_Num(&hour,&key,&test);
			if(test)
				break;
			}
			if(hour>24 || test==2)
			{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Invalid");
				delayS(1);
				goto loop;	
			}
			else
			{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Data Saved");
				alrm_hr=hour;
				delayS(1);
				alrm_flag=1;
				af=1;
				break;
			}
		}
		else if(g_key==3)
		{
			break;
		}
		else
		{
			while(1)
			{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("Set Alarm Minute");
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("MM");
			Read_Num(&min,&key,&test);
			if(test)
				break;
			}
			if(min>59 || test==2)
			{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Invalid");
				delayS(1);
				goto loop;	
			}
			else
			{
				cmdLCD(CLEAR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				strLCD("Data Saved");
				delayS(1);
				alrm_min=min;
				alrm_flag=1;
				af=1;
				break;
			}
		}
	}
}
void displayMenu()
{
	u32 key;
	loop:while(1)
	{  	
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("1.rtc");
		//cmdLCD(GOTO_LINE2_POS0);
		strLCD(" 2.set_alm ");
		cmdLCD(GOTO_LINE2_POS0);
		strLCD("3.Alrm_stat");
		strLCD(" 4.exit");
		key=KeyScan();
		while(ColScan()==0);
		delayMs(100);
		if(key>4 || key==0)
		{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("Invalid");
			delayS(1);
			goto loop;
		}
		switch(key)
		{
			case 1:	while(1)
					{
					Case_1_Call();
					if(g_key==8)
						break;
					Set_RTC_Info_Call();
					}
					break;
			case 2:	while(1)
					{
						Case_2_Call();
						if(g_key==3)
							break;
						Set_Alarm_Call();
					}
					break;	
			case 3:if(alrm_flag)
					{
						cmdLCD(CLEAR_LCD);
						cmdLCD(GOTO_LINE1_POS0);
						U32LCD(alrm_hr);
						charLCD(':');
						U32LCD(alrm_min);
						delayS(1);	
					}	
					else
					{
						cmdLCD(CLEAR_LCD);
						cmdLCD(GOTO_LINE1_POS0);
						strLCD("Alarm not set");
						cmdLCD(GOTO_LINE2_POS0);
						strLCD("set Alarm");	
						delayS(1);
						cmdLCD(CLEAR_LCD);
					}	  	
			case 4:	cmdLCD(CLEAR_LCD);
					break;
			default:cmdLCD(CLEAR_LCD);
					cmdLCD(GOTO_LINE1_POS0);
					strLCD("Invalid");
					delayS(1);
					cmdLCD(CLEAR_LCD);
		}
		if(key==4)
			break;
	} 
}

