#include <STC89C5xRC.H>
#include "Delay.h"
#include "Uart.h"

unsigned char sec = 0;

void main()
{
    Uart_Init();
    while(1)
    {
        Uart_SendByte(sec);
        sec++;
        Delay(1000);
    }
}