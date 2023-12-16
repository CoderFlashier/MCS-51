#include<STC89C5xRC.H>
#include "Delay.h"
#include "DS1302.h"
#include "Uart.h"

//0， 1， 2， 3， 4， 5， 6， 7， 8， 9, -, ., C, L, O对应的段码
unsigned char NixieTable[15] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x40, 0x80, 0x39, 0x38, 0x3F};

void NixieTube_Display(unsigned char location, unsigned char num)
//分别传入显示位置、显示内容
{
    switch(location)
    //选择显示位置
    {
        case 1:
            P24 = 1;
            P23 = 1;
            P22 = 1;
            break;

        case 2:
            P24 = 1;
            P23 = 1;
            P22 = 0;
            break;

        case 3:
            P24 = 1;
            P23 = 0;
            P22 = 1;
            break;

        case 4:
            P24 = 1;
            P23 = 0;
            P22 = 0;
            break;

        case 5:
            P24 = 0;
            P23 = 1;
            P22 = 1;
            break;

        case 6:
            P24 = 0;
            P23 = 1;
            P22 = 0;
            break;

        case 7:
            P24 = 0;
            P23 = 0;
            P22 = 1;
            break;

        case 8:
            P24 = 0;
            P23 = 0;
            P22 = 0;
            break;
    }

    P0 =  NixieTable[num];
    Delay(1);
    //让数码管稳定显示，否则亮度会变低
    //注意STC89C52RC的晶振频率为11.0592MHz，在创建延时函数时应注意选择
    P0 = 0x00;
    //清零
}

extern unsigned char Flicker_Mark;//调用外部变量
extern unsigned char Is_Clock_On;
void NixieTube_DisplayTime(unsigned char Time, unsigned char Flicker_Select)
//数码管显示时间
{    
    if(Flicker_Select == 0)//正常显示，不闪烁
    {
        NixieTube_Display(1, DS1302_Time[Time][0] / 10);
        NixieTube_Display(2, DS1302_Time[Time][0] % 10);
        
        NixieTube_Display(4, DS1302_Time[Time][1] / 10);
        NixieTube_Display(5, DS1302_Time[Time][1] % 10);
        
        NixieTube_Display(7, DS1302_Time[Time][2] / 10);
        NixieTube_Display(8, DS1302_Time[Time][2] % 10);

        if(Flicker_Mark == 0)
        {
            NixieTube_Display(3, 10);
            NixieTube_Display(6, 10);
        }
    }

    if(Flicker_Select == 1)//时闪烁
    {
        if(Flicker_Mark == 0)
        {
            NixieTube_Display(1, DS1302_Time[Time][0] / 10);
            NixieTube_Display(2, DS1302_Time[Time][0] % 10);
        }
    
        NixieTube_Display(4, DS1302_Time[Time][1] / 10);
        NixieTube_Display(5, DS1302_Time[Time][1] % 10);
        
        NixieTube_Display(7, DS1302_Time[Time][2] / 10);
        NixieTube_Display(8, DS1302_Time[Time][2] % 10);

        NixieTube_Display(3, 10);
        NixieTube_Display(6, 10);
    }

    if(Flicker_Select == 2)//分闪烁
    {
        NixieTube_Display(1, DS1302_Time[Time][0] / 10);
        NixieTube_Display(2, DS1302_Time[Time][0] % 10);
        
        if(Flicker_Mark == 0)
        {
            NixieTube_Display(4, DS1302_Time[Time][1] / 10);
            NixieTube_Display(5, DS1302_Time[Time][1] % 10);
        }
        
        NixieTube_Display(7, DS1302_Time[Time][2] / 10);
        NixieTube_Display(8, DS1302_Time[Time][2] % 10);

        NixieTube_Display(3, 10);
        NixieTube_Display(6, 10);
    }

    if(Flicker_Select == 3)//秒闪烁
    {
        NixieTube_Display(1, DS1302_Time[Time][0] / 10);
        NixieTube_Display(2, DS1302_Time[Time][0] % 10);
        
        NixieTube_Display(4, DS1302_Time[Time][1] / 10);
        NixieTube_Display(5, DS1302_Time[Time][1] % 10);
        
        if(Flicker_Mark == 0)
        {
            NixieTube_Display(7, DS1302_Time[Time][2] / 10);
            NixieTube_Display(8, DS1302_Time[Time][2] % 10);
        }

        NixieTube_Display(3, 10);
        NixieTube_Display(6, 10);
    }
}


void NixieTube_DisplayAlarm()
//显示CLOC作为闹钟响起的标志
{
    if(Flicker_Mark == 0)
    {
        NixieTube_Display(1, 12);
        NixieTube_Display(2, 13);
        NixieTube_Display(3, 14);
        NixieTube_Display(4, 12);
    }
}