/*Register Summary
       Bit	Register	Function
       INTEDG	OPTION_REG	Selects rising/falling edge for RB0 interrupt
       INTF	INTCON	External interrupt flag
       INTE	INTCON	Enables RB0 external interrupt
       PEIE	INTCON	Enables peripheral interrupts
       GIE	INTCON	Enables all interrupts globally
*/
#include "interrupt.h"

void Interrupt_Init(void)
{
  TRISB0 = 1;  // RB0 as input

OPTION_REGBITS.INTEDG = 1;
           // INTEDG (Interrupt Edge Select bit) selects which edge triggers the external interrupt.
          // 1 = Rising edge (Low → High)                                             
          // 0 = Falling edge (High → Low)
INTF = 0;
          //INTF is the External Interrupt Flag in the INTCON register.
          //It must be cleared before enabling the interrupt.
          //When an interrupt occurs on RB0, the hardware sets INTF = 1.
INTE =1;
          //INTE is the External Interrupt Enable bit.
          //1 = Enable the RB0/INT external interrupt.
          //0 = Disable the external interrupt.
PEIE = 0;
          //PEIE is the Peripheral Interrupt Enable bit.
          //It is required only for peripheral interrupts (ADC, UART, Timer1, CCP, etc.).
          //Since the RB0 external interrupt is not a peripheral interrupt, PEIE is not needed and can remain 0.
GIE = 1;
           //GIE is the Global Interrupt Enable bit.
           //1 = Enables all interrupts that have been individually enabled.
           //If GIE = 0, no interrupts will be serviced, even if INTE = 1.
}   

// Interrupt Service Routine
void __interrupt() ISR(void)
{
    if(INTF)
    {
        PORTD ^= 0xFF;   // Toggle PORTD
        INTF = 0;        // Clear Interrupt Flag
    }
}
