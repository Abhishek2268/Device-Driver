#include <xc.h>
#include "adc.h"

#define _XTAL_FREQ 32000000UL

void ADC_Init(void)
{
    // RA4 = Analog Input
    TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSA4 = 1;

    // Select AN4
    ADCON0bits.CHS = 0b000100;

    // ADC Configuration
    ADCON1bits.FM = 1;       // Right justified
    ADCON1bits.CS = 0b111;   // ADC Clock = FRC
    ADCON1bits.PREF = 0b00;  // VDD as reference

    // Enable ADC
    ADCON0bits.ON = 1;

    __delay_ms(2);
}

unsigned int ADC_Read(void)
{
    unsigned int result;

    // Select AN4
    ADCON0bits.CHS = 0b000100;

    // Acquisition time
    __delay_us(20);

    // Start ADC conversion
    ADCON0bits.GO = 1;

    // Wait for conversion complete
    while(ADCON0bits.GO);

    // Read 10-bit result
    result = ((unsigned int)ADRESH << 8) | ADRESL;

    return result;
}
