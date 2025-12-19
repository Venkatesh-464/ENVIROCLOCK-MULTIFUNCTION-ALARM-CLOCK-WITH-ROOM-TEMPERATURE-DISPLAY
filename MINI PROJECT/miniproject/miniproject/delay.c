#include"types.h"
void delayUs(u32 dlyus)
{
dlyus*=12;
while(dlyus--);
}
void delayMs(u32 dlyms)
{
dlyms*=12000;
while(dlyms--);
}
void delayS(u32 dlys)
{
dlys*=12000000;
while(dlys--);
}
