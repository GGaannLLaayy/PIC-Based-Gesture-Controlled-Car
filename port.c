
#include <xc.h>
#include "port.h"

void port_Init(void)
{

    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC0 = 0; // A-A   Motor Right side
    TRISCbits.TRISC1 = 0; // A-B   Motor Right side
    TRISCbits.TRISC2 = 0; // B-A   Motor Left side
    TRISCbits.TRISC3 = 0; // B-B   Motor Left side

    PORTCbits.RC0 = 1; // Stop 
    PORTCbits.RC1 = 1; // Stop 
    PORTCbits.RC2 = 1; // Stop
    PORTCbits.RC3 = 1; // Stop


}







