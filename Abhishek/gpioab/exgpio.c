#include <xc.h>
#include "adc.h"



// CONFIG1
#pragma config FEXTOSC = OFF
#pragma config RSTOSC = HFINTOSC_32MHZ
#pragma config CLKOUTEN = OFF
#pragma config VDDAR = HI

// CONFIG2
#pragma config MCLRE = EXTMCLR
#pragma config PWRTS = PWRT_OFF
#pragma config WDTE = OFF
#pragma config BOREN = OFF
#pragma config BORV = LO
#pragma config PPS1WAY = ON
#pragma config STVREN = ON

// CONFIG4
#pragma config BBSIZE = BB512
#pragma config BBEN = OFF
#pragma config SAFEN = OFF
#pragma config WRTAPP = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTSAF = OFF
#pragma config LVP = OFF

// CONFIG5
#pragma config CP = OFF
#define _XTAL_FREQ 32000000UL
void main(void)
{
    unsigned int adc_value;

    // RA0 = LED Output
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 0;

    ADC_Init();

    while(1)
    {
        adc_value = ADC_Read();

        if(adc_value >= 512)
        {
            LATAbits.LATA0 = 1;
        }
        else
        {
            LATAbits.LATA0 = 0;
        }

        __delay_ms(100);
    }
}