#include <STC89C5xRC.H>

void main()
{
    unsigned char LED_num = 0;
    while(1)
    {
        if(P31 == 0)
        {
             Delay(20);
            //这里把Delay作为一个函数放进STC89C5xRC.H里面了，方便后续直接调用
            while (P31 == 0);
            Delay(20);
            //P2默认位1111 1111，即全为高电平
            P2 = ~LED_num;
            LED_num++;
        }
       
    }
}