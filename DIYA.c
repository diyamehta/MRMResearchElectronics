#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 20000000
#pragma config WDT= OFF
#define count PORTBbits.RB0

void BLINK(void)

{
    OSCCON=0x72;
    TRISB=0;
    T0CON=0b01001010;
    TMR0H=0x0B;
    TMR0L=249;
    INTCONbits.TMR0IE=1;
    INTCONbits.GIE=1;
    T0CONbits.TMR0ON=1;
    return;
}
    
    
    
void main()

{
    TRISB=0;
    while(1)
    {
         if (INTCONbits.TMR0IF==1)
         {
        count^=1;
        TMR0H=0x0B;
        TMR0L=249;
        INTCONbits.TMR0IF=0;
        INTCONbits.TMR0IE=0;
        INTCONbits.GIE=0;
        T0CONbits.TMR0ON=0;
    }
        BLINK();
        
    }
}