#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF


void ADC_Init(void)
{
    TRISAbits.TRISA0 = 1;   // RA0 / AN0 = Input

    ADCON1 = 0x80;          // Right justified, VDD/VSS reference
    ADCON0 = 0x41;          // AN0 selected, ADC ON, Fosc/8

    __delay_ms(2);
}


unsigned int ADC_Read(void)
{
    unsigned int result;

    ADCON0bits.CHS = 0;     // Select AN0

    __delay_us(20);

    ADCON0bits.GO = 1;      // Start ADC

    while(ADCON0bits.GO_nDONE);

    result = ((unsigned int)ADRESH << 8) | ADRESL;

    return result;
}


void main(void)
{
    unsigned int adc_value;

    // PORTD as Output
    TRISD = 0x00;

    // Initially all LEDs OFF
    PORTD = 0x00;

    ADC_Init();

    while(1)
    {
        adc_value = ADC_Read();

        if(adc_value >= 512)
        {
            PORTD = 0xFF;       // RD0-RD7 all LEDs ON
        }
        else
        {
            PORTD = 0x00;       // RD0-RD7 all LEDs OFF
        }

        __delay_ms(100);
    }
}