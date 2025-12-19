//ext_int_defines.h

#define EINT0_VIC_CHN0	14
#define EINT1_VIC_CHN0	15

void Init_INT(void);
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
