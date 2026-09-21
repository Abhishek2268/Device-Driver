#include "adc.h"

void ADC_Init(void)
{
    /*
     * RA0 = Analog Input
     */
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSELA0 = 1;

    /*
     * ADC Result = Right Justified
     *
     * FM = 1
     */
    ADCON1bits.FM = 1;

    /*
     * ADC Clock = ADCRC
     *
     * CS = 111
     */
    ADCON1bits.CS = 0b111;

    /*
     * Positive Reference = VDD
     *
     * PREF = 00
     */
    ADCON1bits.PREF = 0b00;

    /*
     * No automatic conversion trigger
     */
    ADACT = 0x00;

    /*
     * Select RA0 initially
     */
    ADCON0bits.CHS = ADC_CHANNEL_RA0;

    /*
     * Turn ADC ON
     */
    ADCON0bits.ON = 1;
}


uint16_t ADC_Read(uint8_t channel)
{
    uint16_t result;

    /*
     * Select ADC channel
     */
    ADCON0bits.CHS = channel;

    /*
     * Acquisition delay
     *
     * Give sample/hold capacitor
     * sufficient time to charge.
     */
    __delay_us(5);

    /*
     * Start ADC conversion
     */
    ADCON0bits.GO = 1;

    /*
     * Wait until conversion completes
     */
    while (ADCON0bits.GO)
    {
        ;
    }

    /*
     * Read 10-bit ADC result
     *
     * Result is right justified.
     */
    result = ((uint16_t)ADRESH << 8) | ADRESL;

    /*
     * 10-bit result = 0 to 1023
     */
    return result;
}