#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000
#pragma config WDT= OFF

char hscnd = 0;
int count = 0;
char get_scnds =0;
char flag =0;
char i=0;

void __interrupt() isr(void)
{  
    if(TMR0IF==1) // Timer flag has been triggered due to timer overflow
    {
        TMR0 = 100;     //Load the timer Value
        INTCONbits.TMR0IF=0;       // Clear timer interrupt flag
        count++;
    } 
    
    if (count == 250)
    {
        hscnd+=1;   // hscnd will get incremented for every half second
        count=0;
    }
}

void main()
{    unsigned char OPTION_REG;
/*Port Configuration for Timer **/
    OPTION_REG = 0b00000101;  // Timer0 with external freq and 64 as prescalar // Also Enables PULL UPs
    TMR0=100;       // Load the time value for 0.0019968s; delayValue can be between 0-256 only
    INTCONbits.TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    INTCONbits.GIE=1;          //Enable Global Interrupt
    INTCONbits.PEIE=1;         //Enable the Peripheral Interrupt
    /*__*/   
 
    /*Port Configuration for I/O **/
    TRISA=1; //Instruct the MCU that the PORTB pin 1 is used as input for button 1.
    TRISB = 0x00; //Instruct the MCU that all pins on PORT D are output 
    PORTB=0x00; //Initialize all pins to 0
    /*__*/   

    while(1)
    {
        count =0; //Do not run timer while in main loop
        
        //*Get the number delay from user//////
        if (PORTAbits.RA0==0 && flag==0) //When input given
        {
            get_scnds+=1; //get_scnds=get_scnds+1//Increment variable 
            flag=1;
        }
        if (PORTAbits.RA0==1) //To prevent continuous incrementation
            flag=0;
        /*__*/ 
        
        
        //*Execute sequence with delay//////
        while (PORTAbits.RA0==0)
        {
                PORTB = 0b00000001<<i;  //Left shit LED by i
                if(hscnd==get_scnds) //If the required time is reached
                {
                    i+=1; //Move to next LED after the defined Delay
                    hscnd=0;  
                }
                flag=2;
        }
        if (flag==2 && PORTAbits.RA0==1) //Reset timer if button is high again
        {
            get_scnds=0;hscnd=0;i=0;  
            PORTB=0; //Turn off all LEDs
        }
        /*__*/ 
    }
}
