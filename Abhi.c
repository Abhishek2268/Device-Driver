#include <xc.h>

#define _XTAL_FREQ 32000000UL


// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator Mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_32MHZ// Power-up Default Value for COSC bits (HFINTOSC (32 MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O function on RA4)
#pragma config VDDAR = HI       // VDD Range Analog Calibration Selection bit (Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V)

// CONFIG2
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR)
#pragma config PWRTS = PWRT_OFF // Power-up Timer Selection bits (PWRT is disabled)
#pragma config WDTE = OFF       // WDT Operating Mode bits (WDT disabled; SEN is ignored)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection bit (Brown-out Reset Voltage (VBOR) set to 1.9V)
#pragma config PPS1WAY = ON     // PPSLOCKED One-Way Set Enable bit (The PPSLOCKED bit can be set once after an unlocking sequence is executed; once PPSLOCKED is set, all future changes to PPS registers are prevented)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3

// CONFIG4
#pragma config BBSIZE = BB512   // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF       // Boot Block Enable bit (Boot Block is disabled)
#pragma config SAFEN = OFF      // SAF Enable bit (SAF is disabled)
#pragma config WRTAPP = OFF     // Application Block Write Protection bit (Application Block is not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block is not write-protected)
#pragma config WRTC = OFF       // Configuration Registers Write Protection bit (Configuration Registers are not write-protected)
#pragma config WRTSAF = OFF     // Storage Area Flash (SAF) Write Protection bit (SAF is not write-protected)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (High Voltage on MCLR/Vpp must be used for programming)

// CONFIG5
#pragma config CP = OFF         // User Program Flash Memory Code Protection bit (User Program Flash Memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

void ADC_Init(void)
{
    // RA4 = ADC input
    TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSA4 = 1;

    // Select RA4 = ANA4
    ADCON0bits.CHS = 0b000100;

    // ADC:
    // FM = 1       -> Right justified
    // CS = 111     -> ADCRC
    // PREF = 00    -> VDD reference
    ADCON1bits.FM = 1;
    ADCON1bits.CS = 0b111;
    ADCON1bits.PREF = 0b00;

    // ADC ON
    ADCON0bits.ON = 1;

    __delay_ms(2);
}


unsigned int ADC_Read(void)
{
    unsigned int result;

    // RA4 / ANA4
    ADCON0bits.CHS = 0b000100;

    // Acquisition time
    __delay_us(20);

    // Start conversion
    ADCON0bits.GO = 1;

    // Wait for conversion complete
    while(ADCON0bits.GO);

    // Read 10-bit result
    result = ((unsigned int)ADRESH << 8) | ADRESL;

    return result;
}


void main(void)
{
    unsigned int adc_value;

    // RA0 = LED output
    TRISAbits.TRISA0 = 0;

    // LED OFF
    LATAbits.LATA0 = 0;

    // ADC initialization
    ADC_Init();

    while(1)
    {
        adc_value = ADC_Read();

        if(adc_value >= 512)
        {
            // LED ON
            LATAbits.LATA0 = 1;
        }
        else
        {
            // LED OFF
            LATAbits.LATA0 = 0;
        }

        __delay_ms(100);
    }
}-
