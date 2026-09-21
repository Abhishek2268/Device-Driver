#include <xc.h>
#include <stdint.h>
#include "adc.h"

#define _XTAL_FREQ 4000000

void main(void)
{
    uint16_t adc_value;

    ADC_Init();

    while(1)
    {
        adc_value = ADC_Read(ADC_CHANNEL_RA0);

        /*
         * adc_value:
         *
         * 0V       -> approximately 0
         * VDD      -> approximately 1023
         *
         * Example:
         * VDD = 5V
         * 2.5V input -> approximately 512
         */

        __delay_ms(100);
    }
}