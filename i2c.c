#include<xc.h>
#include<stdlib.h>
#include<stdio.h>
#include <pic18f452.h>
#define _XTAL_FREQ 8000000

void I2C_Master_Init(const unsigned long c)
{
  SSPCON1 = 0b00101000;
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  SSPSTAT = 0;
  TRISC3 = 1;        //Setting as input as given in data sheet
  TRISC4 = 1;        //Setting as input as given in data sheet
}

void I2C_Master_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
  I2C_Master_Wait();
  SEN = 1;
}

void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  RSEN = 1;
}

void I2C_Master_Stop()
{
  I2C_Master_Wait();
  PEN = 1;
}

void I2C_Master_Write(unsigned d)
{
  I2C_Master_Wait();
  SSPBUF = d;
}

unsigned short I2C_Master_Read(unsigned short a)
{
  unsigned short temp;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  temp = SSPBUF;
  I2C_Master_Wait();
  ACKDT = (a)?0:1;
  ACKEN = 1;
  return temp;
}

void main()
{
  TRISC = 0xFF;                 //PORTB as input
  I2C_Master_Init(100000);      //Initialize I2C Master with 100KHz clock
  while(1)
  {
    I2C_Master_Start();         //Start condition
    I2C_Master_Write(0x30);     //7 bit address + Write
    I2C_Master_Write(PORTB);    //Write data
    I2C_Master_Stop();          //Stop condition
    __delay_ms(200);
    I2C_Master_Start();         //Start condition
    I2C_Master_Write(0x31);     //7 bit address + Read
    PORTA = I2C_Master_Read(0); //Read + Acknowledge
    I2C_Master_Stop();          //Stop condition
    __delay_ms(200);
  }
}