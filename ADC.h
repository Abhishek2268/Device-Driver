#ifndef ADC_H
#define ADC_H

#include <xc.h>
#include <stdint.h>

#define ADC_CHANNEL_RA0     0x00
#define ADC_CHANNEL_RA1     0x01
#define ADC_CHANNEL_RA2     0x02
#define ADC_CHANNEL_RA4     0x04
#define ADC_CHANNEL_RA5     0x05

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

#endif