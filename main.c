/*
 * File:   main.c
 * Author: Wai Moe Oo and Chan Myae Aung
 *
 * Created on July 22, 2018, 10:02 PM
 */
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "port.h"
#include "usart.h"

#define _XTAL_FREQ   4000000

char serialAvailable(void);
void stop_motor(void);

char tx_tick = 1;
char rx_temp, flag;
char state, readdata;

void main(void)
{
    port_Init();
    serial_init();


    while (1)
    {
        if (serialAvailable())
        {
            readdata = state;
            switch (state)
            {
            case 'F': // Motor Forward

                PORTCbits.RC0 = 0; // In 1
                PORTCbits.RC1 = 1; // In 2
                PORTCbits.RC3 = 1; // In 3
                PORTCbits.RC2 = 0; // In 4                
                state = 0;
                __delay_ms(200);
                break;
            case 'B': // Motor Reverse

                PORTCbits.RC0 = 1; // In 1
                PORTCbits.RC1 = 0; // In 2 
                PORTCbits.RC3 = 0; // In 3 
                PORTCbits.RC2 = 1; // In 4
                state = 0;
                __delay_ms(200);
                break;
            case 'R': // Motor Turn Right

                PORTCbits.RC0 = 0; // A-A High
                PORTCbits.RC1 = 1; // A-B Low
                PORTCbits.RC3 = 1; // B-B High  // stop B 
                PORTCbits.RC2 = 1; // B-A Low   // stop B
                state = 0;
                __delay_ms(200);
                break;
            case 'L': // Motor Turn Left

                PORTCbits.RC0 = 1; // A-A High  // stop A
                PORTCbits.RC1 = 1; // A-B Low   // stop A
                PORTCbits.RC3 = 1; // B-B High
                PORTCbits.RC2 = 0; // B-A Low          
                state = 0;
                __delay_ms(200);
                break;
            
            case 'S': // Motor Turn Back Left
                stop_motor();

                state = 0;
                __delay_ms(200);
                break;
            default:
                PORTCbits.RC0 = 0; // Stop 
                PORTCbits.RC1 = 0; // Stop 
                PORTCbits.RC3 = 0; // Stop
                PORTCbits.RC2 = 0; // Stop
                break;



        }
    }
}
}


    void __interrupt() isr(void)
    {
        if (RCIF)
        {
            rx_temp = RCREG;
            if (RCSTAbits.OERR)
            {
                RCSTAbits.CREN = 0;
                NOP();
                NOP();
                RCSTAbits.CREN = 1;
            }

            flag = 1;
        }
    }

    char serialAvailable(void)
    {
        flag = 0;
        state = rx_temp;
        return state;
    }

    void stop_motor(void)
    {
        PORTCbits.RC0 = 0; // Stop 
        PORTCbits.RC1 = 0; // Stop 
        PORTCbits.RC2 = 0; // Stop
        PORTCbits.RC3 = 0; // Stop
    }