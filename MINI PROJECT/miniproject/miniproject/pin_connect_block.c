#include<LPC21xx.h>
#include"types.h"
void cfgPortPinFunc(u32 Port,u32 Pin,u32 Func)
{
		if(Port==0)
		{
			if(Pin<=15)
			{
				PINSEL0=((PINSEL0&(~(3<<Pin*2)))|(Func<<(Pin*2)));
			}
			else if((Pin>=16)&&(Pin<=31))
			{
					PINSEL1=((PINSEL1&(~(3<<((Pin-16)*2))))|(Func<<(Pin-16)*2));
			}
		}
}
