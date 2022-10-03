#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#pragma config WDT= OFF
#define BAUDRATE 9600

void uart(char data)
{
    while(TXIF==0);  
    TXIF=0;          
    TXREG=data;        
}
int main()
{
    OSCCON=0x72; 
    INTCONbits.GIEH=1;
    INTCONbits.GIEL=1;
    TRISCbits.RC6=0;
    TRISCbits.RC7=1;
    TXSTAbits.TX9=0;
    TXSTAbits.TXEN=1;
    TXSTAbits.SYNC=0;
    TXSTAbits.BRGH=1;
    PIE1bits.TXIE=0;
    PIE1bits.RCIE=0;
    RCSTAbits.SPEN=1;
    RCSTAbits.RX9=0;
    RCSTAbits.CREN=1;
   
    SPBRG=52;
    
    char i,a[]={"hi"};
    char ch;

    
    for(i=0;a[i]!=0;i++)
    {
        uart(a[i]); 
    
    }
}
