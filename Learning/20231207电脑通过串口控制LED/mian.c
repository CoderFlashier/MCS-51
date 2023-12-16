#include <STC89C5xRC.H>
#include "Delay.h"
#include "Uart.h"

unsigned char sec = 0;

void main()
{
    Uart_Init();
    while(1)
    {

    }
}


void Uart_Routine() interrupt 4
//出发接收中断后的操作
{
	if(RI == 1)
    //防止发送中断导致操作进行
    {
        P2 = SBUF;
        //读取数据
        Uart_SendByte(SBUF);
        //发送接收到的数据
        RI = 0;
        //清零
    }
}