#include <STC89C5xRC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"


unsigned char second = 0;
unsigned char minute = 0;
unsigned char hour = 0;
void main()
{
    Timer0_Init();
    LCD_Init();
    LCD_ShowString(1, 1, "Clock:");
    while(1)
    {
        LCD_ShowNum(2, 1, hour, 2);
        LCD_ShowString(2, 3, ":");
        LCD_ShowNum(2, 4, minute, 2);
        LCD_ShowString(2, 6, ":");
        LCD_ShowNum(2, 7, second, 2);
    }
}


void Timer0_Isr(void) interrupt 1
{
    static unsigned int T0_count = 0;

	TL0 = 0x66;
	TH0 = 0xFC;	

    T0_count++;
    if(T0_count >= 1000)
    {
        T0_count = 0;
        second++;
        //LCD_ShowNum不宜放在这里，该函数运行时间较长
        //中断函数中不应执行时间较长的操作

        if(second == 60)
        {
            second = 0;
            minute++;
            if(minute == 60)
            {
                minute = 0;
                hour++;
                if(hour == 24)
                {
                    hour = 0;
                }
            }
            
        }
    }
}