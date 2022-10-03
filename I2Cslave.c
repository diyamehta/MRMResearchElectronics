#include<xc.h>
#include<stdlib.h>
#include<stdio.h> 
#define _XTAL_FREQ 8000000
short z;
void interrupt I2C_Slave_Read()
{
  if(SSPIF == 1)
  {
    SSPCON1bits.CKP = 0;

    if ((SSPCON1bits.SSPOV) || (SSPCON1bits.WCOL))
    {
      z = SSPBUF; // Read the previous value to clear the buffer
      SSPCON1bits.SSPOV = 0; // Clear the overflow flag
      SSPCON1bits.WCOL = 0;  // Clear the collision bit
      SSPCON1bits.CKP = 1;
    }
    if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW)
    {
      z = SSPBUF;
      while(!BF);
      PORTD = SSPBUF;
      SSPCON1bits.CKP = 1;
    }
    else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)
    {
      z = SSPBUF;
      BF = 0;
      SSPBUF = PORTB;
      SSPCON1bits.CKP = 1;
      while(SSPSTATbits.BF);
    }

    SSPIF = 0;
  }
}

void I2C_Slave_Init(short address)
{
  SSPSTAT = 0x80;
  SSPADD = address;
  SSPCON1 = 0x36;
  SSPCON2 = 0x01;
  TRISC3 = 1;   //Setting as input as given in datasheet
  TRISC4 = 1;   //Setting as input as given in datasheet
  GIE = 1;
  PEIE = 1;
  SSPIF = 0;
  SSPIE = 1;
}

void main()
{
  TRISC = 0xFF;         //PORTC as input
  I2C_Slave_Init(0x30); //Initialize as a I2C Slave with address 0x30
  while(1);
}
