//rtc.c
#include <LPC214x.H>
#include "lcd_defines.h"
#include "lcd.h"
#include "rtc_defines.h"
#include "types.h"

s8 week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

//Intialise RTC
void Init_RTC(void)
{
	 // Disable and reset the RTC
	CCR = RTC_RESET;
 
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
  
  // Enable the RTC
	CCR = RTC_ENABLE|(1<<4);//|RTC_CKLSCR;  
}

//set RTC Time,Date,Day
void SetRTCTimeInfo(u32 hour,u32 min,u32 sec)
{
	HOUR=hour;
	MIN=min;
	SEC=sec;
}
void SetRTCDateInfo(u32 date,u32 month,u32 year)
{
	DOM=date;
	MONTH=month;
	YEAR=year;
}
void SetRTCDay(u32 dayofweek)
{
	DOW=dayofweek;
}

//get and display Time
void GetRTCTimeInfo(s32 *hour,s32 *min,s32 *sec)
{
	*hour=HOUR;
	*min=MIN;
	*sec=SEC;
}
void DisplayRTCTime(s32 hour,s32 min,s32 sec)
{
	cmdLCD(GOTO_LINE1_POS0);
	charLCD((hour/10)+48);
	charLCD((hour%10)+48);
	charLCD(':');
	charLCD((min/10)+'0');
	charLCD((min%10)+'0');
	charLCD(':');
	charLCD((sec/10)+0x30);
	charLCD((sec%10)+0x30);
}

//get and display Date
void GetRTCDateInfo(s32 *date,s32 *month,s32 *year)
{
	*date=DOM;
	*month=MONTH;
	*year=YEAR;
}
void DisplayRTCDate(s32 date,s32 month,s32 year)
{
	u32 yr;
	cmdLCD(GOTO_LINE2_POS0);
	charLCD((date/10)+48);
	charLCD((date%10)+48);
	charLCD('/');
	charLCD((month/10)+48);
	charLCD((month%10)+48);
	charLCD('/');
	yr=year%100;
	if(yr<=9)
	{
	charLCD('0');
	charLCD(yr+48);
	}
	else
	U32LCD(yr);
}

//get and diaplay Day
void GetRTCDay(s32 *dayofweek)
{
	*dayofweek=DOW;
}

void DisplayRTCDay(u32 dayofweek)
{
	cmdLCD(GOTO_LINE1_POS0+9);
	strLCD(week[dayofweek]);
}

/*void SetRTCHour(u32);
void SetRTCMin(u32);
void SetRTCSec(u32);
void SetRTCDate(u32);
void SetRTCMonth(u32);
void SetRTCYear(u32);
void SetRTCDay(u32);

void GetRTCHour(s32 *);
void GetRTCMin(s32 *);
void GetRTCSec(s32 *);
void GetRTCDate(s32 *);
void GetRTCMonth(s32 *);
void GetRTCYear(s32 *);
void GetDay(void);*/

