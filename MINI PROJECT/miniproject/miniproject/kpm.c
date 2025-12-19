//kpm.c
#include<lpc21xx.h>
#include "types.h"
#include "defines.h"
#include "kpm_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
/*u32 kpmLUT[4][4]=
{{1,5,9,13},
 {2,6,10,14},
 {3,7,11,15},
 {4,8,12,16}
};*/
/*u32 kpmLUT[4][4]={	{1,2,3,111},
					{4,5,6,111},
					{7,8,9,111},
					{0,32,88,111}};
			  */
u8 kpmLUT[4][4]={	{'7','8','9','A'},
					{'4','5','6','a'},
					{'1','2','3','$'},
					{'0','#',32,'@'}
				};


void Init_KPM(void)
{
	//cfg row lines as gpio output lines and ground all rowa
	WRITEBYTE(IODIR1,ROWs_4,15);
	//cfg col lines as gpio input default input
}
u32 ColScan(void)
{
	return (READNIBBLE(IOPIN1,COLs_4)<15)?0:1;
}
u32 RowCheck(void)
{
	u32 r;
	for(r=0;r<4;r++)
	{
	//ground one row at a time from 0th row
	WRITENIBBLE(IOPIN1,ROWs_4,~(1<<r));
	//check if key was pressed in that row
	if(ColScan()==0)
	{
		break;
	}
	}
	//reintilaize all rows to ground
	WRITENIBBLE(IOPIN1,ROWs_4,0);
	return r;
}
u32 ColCheck(void)
{
	u32 c;
	for(c=0;c<4;c++)
	{
	if(READBIT(IOPIN1,COL0+c)==0)
	{
		break;
	}
	}
	return c;
}
u32 KeyScan(void)
{
	u32 r,c,keyv;
	//wait to detect any key press
	while(ColScan());
	//if key press detected 
	//identify row in which key was pressed
	r=RowCheck();
	//identify col in which key was pressed
	c=ColCheck();
	//map key value to press key
	keyv=kpmLUT[r][c];
	return keyv;
}

void Read_Num(u32 *num,u8 *key,u32 *test)
{
	u32 i=0;
	*test=1;
	*num=0;
	loop:while(1)
	{
	if(i==3)
		break;
	*key=KeyScan();
	while(ColScan()==0);
	delayMs(100);
	if(i==0)
	{
		if(*key==32 || *key==88)
		{
			*test=0;
			break;
		}
	}
	if(i>0)
	{
		if(*num==0)
		{
			*test=2;
			break;
		}
	} 
	if(*key==88)
		break;
	else if(*key==111)
		goto loop;
	else if(*key==32)
	{
		*num=*num/10;
		cmdLCD(GOTO_LINE2_POS0);
		if(*num==0)
			charLCD(' ');
		else
		{
			U32LCD(*num);
			charLCD(' ');
		}
	}
	else
	{
		i++;
		*num=((*num)*10)+*key;
		cmdLCD(GOTO_LINE2_POS0);
		U32LCD(*num);
		if(*num<=0);
			charLCD(' ');
	}
	}
}
void Read_Num_Year(u32 *num,u8 *key,u32 *test)
{
	u32 i=0;
	*test=1;
	*num=0;
	loop:while(1)
	{
	if(i==5)
		break;
	*key=KeyScan();
	while(ColScan()==0);
	delayMs(100);
	if(i==0)
	{
		if(*key==32 || *key==88)
		{
			*test=0;
			break;
		}
	} 
	if(*key==88)
		break;
	else if(*key==111)
		goto loop;
	else if(*key==32)
	{
		*num=*num/10;
		cmdLCD(GOTO_LINE2_POS0);
		if(*num==0)
			charLCD(' ');
		else
		{
		U32LCD(*num);
		charLCD(' ');
		}
	}
	else
	{
		i++;
		*num=((*num)*10)+*key;
		cmdLCD(GOTO_LINE2_POS0);
		U32LCD(*num);
		if(*num<=0);
		charLCD(' ');
	}
	}
} 
/*void Read_Num(u32 *num,u8 *key)
{
	*num=0;
	while(1)
	{
	*key=KeyScan();
	if(*key>='0' && *key<='9')
	{
		*num=(*num*10)+(*key-48);
		cmdLCD(GOTO_LINE2_POS0);
		U32LCD(*num);
		while(ColScan()==0);
	}
	else
	{
		charLCD(' ');
		charLCD(*key);
		while(ColScan()==0);
		break;
	}
	}
}*/
