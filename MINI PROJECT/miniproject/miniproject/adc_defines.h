//adc_defines.h
#ifndef __ADC_DEFINES_H
#define __ADC_DEFINES_H
#define FOSC 		12000000
#define CCLK 		(FOSC*5)
#define PCLK 		(CCLK/4)
#define ADCCLK 		3000000//approx <=4.5Mhz
#define CCLKDIV 	((PCLK/ADCCLK)-1)

//ADCR SFR DEFINES
#define CCLK_DIV_BIT 		8
#define PDN_BIT 				21
#define ADC_START_BIT 	24

//ADDR SFR DEFINES
#define RESULT_BIT 		6
#define DONE_BIT		 	31
#endif
