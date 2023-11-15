#include <STC89C5xRC.H>

void main()
{
    unsigned char LED_num = 0;
    P2 = ~0x01;
    // 亮起第一个灯
    while(1)
    {
        //按下K1时，亮灯右移
        if(P31 == 0)
        {
            Delay(20);
            while(P31 == 0);
            Delay(20);
            
            if (LED_num == 7)
            {
                LED_num = 0;
            }
            else
            {
                LED_num++;
            }
            P2 = ~(0x01 << LED_num);

        }

        //当按下K2时，亮灯左移
        if(P30 == 0)
        {
            Delay(20);
            while(P30 == 0);
            Delay(20);
            
            if(LED_num == 0)
            {
                LED_num = 7;
            }
            else
            {
                LED_num--;
            }
            P2 = ~(0x01 << LED_num);
            
        }
    }
}