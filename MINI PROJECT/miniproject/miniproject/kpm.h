//kpm.h
#include "types.h"
void Init_KPM(void);
u32 ColScan(void);
u32 RowCheck(void);
u32 ColCheck(void);
u32 KeyScan(void);
void Read_Num(u32 *num,u8 *key,u32 *test);
void Read_Num_Year(u32 *num,u8 *key,u32 *test);
