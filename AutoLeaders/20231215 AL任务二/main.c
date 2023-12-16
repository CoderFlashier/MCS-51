#include <STC89C5xRC.H>
#include "DS1302.h"
#include "NixieTube_Display.h"
#include "Delay.h"
#include "Uart.h"
#include "Timer0.h"
#include "MatrixKey.h"
#include "MatrixLED.h"


void main()
{
    unsigned char Current_Time = 0;
    unsigned char Mode = 0;
   // unsigned char Time_Select = 0;//在调整时间的时候选择位数
    unsigned char Is_Clock_On = 0;//闹钟是否开启
    unsigned char Clock_Mark = 0;//闹钟是否响起


    unsigned char Key_Num = 0;
    unsigned char last_Key_Num = 0;

    unsigned char i = 0;
    int j = 0;


    DS1302_Init();
    DS1302_SetTime();//设定初始时间

    Uart_Init();
    Timer0_Init();

    while(1)
    {
        Key_Num = MatrixKey();
        if(Key_Num == 8 && last_Key_Num == 0)
        //在矩阵键盘的输入中不添加死循环，通过对上一次按键值和这一次的按键值的判断来实现按键不影响程序运行的效果
        {
            if(Mode = 1) DS1302_SetTime(); //设置调整后的时间
            Mode = 0;//计时模式
            //Time_Select = 0;//重置时间选择
        }

        if(Key_Num == 4 && last_Key_Num == 0)
        {
            Mode = 1;//调整时间
        }
        if(Key_Num == 16 && last_Key_Num == 0)
        {
            Uart_SentTime();//发送时间
        }
        
        if(Key_Num == 9 && last_Key_Num == 0)
        {
            Mode = 3;//调整闹钟时间
        }

        if(Key_Num == 10 && last_Key_Num == 0)
        {
            Is_Clock_On++;
            Is_Clock_On %= 2;//开关闹钟
        }
        last_Key_Num = Key_Num;


        switch(Mode)
        {   
            case 0:
            //计时模式
                if(Is_Clock_On == 1)
                {
                    NixieTube_Display(8, 11);
                    if(Clock_Mark == 0) Clock_Mark = Is_Clock_Alarm();

                    if(Clock_Mark == 1)
                    {
                        j++;
                        if(j < 2000) NixieTube_DisplayAlarm();//显示CLOC模拟闹钟响起
                        DS1302_ReadTime();
                        if(j == 2000)
                        {
                            j = 0;
                            Clock_Mark = 0;
                        }
                    }
                    else
                    {
                        DS1302_ReadTime();
                        NixieTube_DisplayTime(0, 0);
                    }
                }
                else
                {
                    DS1302_ReadTime();
                    NixieTube_DisplayTime(0, 0);
                }
                break;
        
            case 1:
            //调节模式
                DS1302_TimeChange(0);
                //第一个参数置0时调整时钟，置1调整闹钟
                if(Is_Clock_On == 1) NixieTube_Display(8, 11);
                break;
            
            case 3: 
            //调整闹钟
                DS1302_TimeChange(1);
                if(Is_Clock_On == 1)  NixieTube_Display(8, 11);
                break;
        }

    }
}


unsigned char Flicker_Mark = 0;//用于标记亮灭
void Timer0_Isr(void) interrupt 1
{
    static unsigned int T0_count = 0;

	TL0 = 0x66;
	TH0 = 0xFC;

    T0_count++;
    if(T0_count >= 500)
    {
        T0_count = 0;
        Flicker_Mark = ~Flicker_Mark;
    }
}