//lcd.h
#ifndef __LCD_H
#define __LCD_H
#include "types.h"

void Init_LCD(void);
void writeLCD(u32 byte);
void cmdLCD(u32 cmd);
void charLCD(u32 ascii);
void strLCD(s8 *);
void U32LCD(u32);
void S32LCD(s32);
void F32LCD(f32,u32);
void Build_CGRAM(u8 *,u8);
#endif


