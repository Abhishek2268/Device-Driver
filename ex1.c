#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000

// ADC functions
void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

void ADC_Init(void)
{
    // RA0 = Analog input
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;

    // ADC configuration
    ADCON1bits.FM = 1;       // Right justified
    ADCON1bits.CS = 0b111;   // ADCRC
    ADCON1bits.PREF = 0b00;  // VDD reference

    ADCON0bits.CHS = 0;      // AN0 / RA0
    ADCON0bits.ON = 1;       // ADC ON

    __delay_us(10);
}

uint16_t ADC_Read(uint8_t channel)
{
    uint16_t result;

    // Select channel
    ADCON0bits.CHS = channel;

    // Acquisition time
    __delay_us(10);

    // Start conversion
    ADCON0bits.GO = 1;

    // Wait for conversion
    while (ADCON0bits.GO)
    {
        ;
    }

    // Read 10-bit result
    result = ((uint16_t)ADRESH << 8) | ADRESL;

    return result;
}

void main(void)
{
    uint16_t adc_value;

    // LED on RA4
    TRISAbits.TRISA4 = 0;
    ANSELAbits.ANSELA4 = 0;
    LATAbits.LATA4 = 0;

    ADC_Init();

    while(1)
    {
        // Read potentiometer from RA0 / AN0
        adc_value = ADC_Read(0);

        // Pot high
        if(adc_value >= 512)
        {
            LATAbits.LATA4 = 1;     // LED ON
        }
        else
        {
            LATAbits.LATA4 = 0;     // LED OFF
        }

        __delay_ms(50);
    }
}
