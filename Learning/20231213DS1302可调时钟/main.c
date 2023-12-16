#include <STC89C5xRC.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "Timer0.h"
#include "Key.h"

unsigned char Second = 0;
unsigned char Minute = 0;
unsigned char KeyNum = 0;
unsigned char Mode = 0;
unsigned char TimeSet_Select = 0;
unsigned char TimeSet_Flag = 0;

void TimeShow()
{
    DS1302_ReadTime();
    LCD_ShowNum(1, 1, DS1302_Time[0], 2);
    LCD_ShowNum(1, 4, DS1302_Time[1], 2);
    LCD_ShowNum(1, 7, DS1302_Time[2], 2);
    LCD_ShowNum(2, 1, DS1302_Time[3], 2);
    LCD_ShowNum(2, 4, DS1302_Time[4], 2);
    LCD_ShowNum(2, 7, DS1302_Time[5], 2);
    Delay(50);
}

unsigned char LongMonth[] = {1, 3, 5, 7, 8, 10 ,12};
unsigned char ShortMonth[] = {4, 6, 9, 11};

void TimeSet()
{
    unsigned char i = 0;
    if(KeyNum == 2)
    {
        TimeSet_Select++;
        TimeSet_Select %= 6;
    }
    if(KeyNum == 3)//加
    {
        DS1302_Time[TimeSet_Select]++;
        
        //合法性检查
        if(DS1302_Time[0] > 99) DS1302_Time[0] = 0;
        if(DS1302_Time[1] > 12) DS1302_Time[1] = 1;

        for(i = 0; i < 7; i++)
        {
            if(DS1302_Time[1] == LongMonth[i])//判断是否为大月
            {
                if(DS1302_Time[2] > 31) DS1302_Time[2] = 1;
            }
        }
        for(i = 0;i < 4;i++)
        {
            if(DS1302_Time[1] == ShortMonth[i])//判断是否为小月
            {
                if(DS1302_Time[2] > 30) DS1302_Time[2] = 1;
            }
        }
        if(DS1302_Time[1] == 2)
        {
            if(DS1302_Time[0] % 4 == 0)
            //判断闰年，DS1302只有99年的计时，不用考虑是否逢百
            {
                if(DS1302_Time[2] > 29) DS1302_Time[2] = 1;
            }
            else
            {
                if(DS1302_Time[2] > 28) DS1302_Time[2] = 1;
            }
        }


        if(DS1302_Time[3] > 23) DS1302_Time[3] = 0;
        if(DS1302_Time[4] > 59) DS1302_Time[4] = 0;
        if(DS1302_Time[5] > 59) DS1302_Time[5] = 0;
    }
    if(KeyNum == 4)//减
    {
        DS1302_Time[TimeSet_Select]--;


        //这里将数据改为有符号类型，方便判断（注意头文件中的unsigned也要去掉）
        if(DS1302_Time[0] < 0) DS1302_Time[0] = 99;
        if(DS1302_Time[1] < 1) DS1302_Time[1] = 12;


        if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 ||DS1302_Time[1] == 5 ||DS1302_Time[1] == 7 ||
          DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)//判断是否为大月
        {
            if(DS1302_Time[2] < 1) DS1302_Time[2] = 31;
        }
        else if(DS1302_Time[1] == 4 ||DS1302_Time[1] == 6 ||DS1302_Time[1] == 9 ||
                DS1302_Time[1] == 11)//判断是否为小月
        {
            if(DS1302_Time[2] < 1) DS1302_Time[2] = 30;
            if(DS1302_Time[2] > 30) DS1302_Time[2] = 1;
        }
        else if(DS1302_Time[1] == 2)
        {
            if(DS1302_Time[0] % 4 == 0)
            //判断闰年，DS1302只有99年的计时，不用考虑是否逢百
            {
                if(DS1302_Time[2] < 1) DS1302_Time[2] = 29;
                if(DS1302_Time[2] > 29) DS1302_Time[2] = 1;
            }
            else
            {
                if(DS1302_Time[2] < 1) DS1302_Time[2] = 28;
                if(DS1302_Time[2] > 28) DS1302_Time[2] = 1;
            }
        }


        if(DS1302_Time[3] < 0) DS1302_Time[3] = 23;
        if(DS1302_Time[4] < 0) DS1302_Time[4] = 59;
        if(DS1302_Time[5] < 0) DS1302_Time[5] = 59;
    }
    //LCD_ShowNum(2, 10, TimeSet_Select, 2);


    //更新显示，同时实现闪烁
    if(TimeSet_Select == 0 && TimeSet_Flag == 1)
    {
        LCD_ShowString(1, 1, "  ");
    }
    else
    {
        LCD_ShowNum(1, 1, DS1302_Time[0], 2);
    }

    if(TimeSet_Select == 1 && TimeSet_Flag == 1)
    {
        LCD_ShowString(1, 4, "  ");
    }
    else
    {
        LCD_ShowNum(1, 4, DS1302_Time[1], 2);
    }

    if(TimeSet_Select == 2 && TimeSet_Flag == 1)
    {
        LCD_ShowString(1, 7, "  ");
    }
    else
    {
        LCD_ShowNum(1, 7, DS1302_Time[2], 2);
    }

    if(TimeSet_Select == 3 && TimeSet_Flag == 1)
    {
        LCD_ShowString(2, 1, "  ");
    }
    else
    {
        LCD_ShowNum(2, 1, DS1302_Time[3], 2);
    }

    if(TimeSet_Select == 4 && TimeSet_Flag == 1)
    {
        LCD_ShowString(2, 4, "  ");
    }
    else
    {
        LCD_ShowNum(2, 4, DS1302_Time[4], 2);
    }

    if(TimeSet_Select == 5 && TimeSet_Flag == 1)
    {
        LCD_ShowString(2, 7, "  ");
    }
    else
    {
        LCD_ShowNum(2, 7, DS1302_Time[5], 2);
    }
}


void main()
{
    LCD_Init();
    LCD_ShowString(1, 1, "  -  -  ");
    LCD_ShowString(2, 1, "  :  :  ");

    DS1302_Init();
    DS1302_SetTime();

    Timer0_Init();

    while(1)
    {
        KeyNum = Key();
        if(KeyNum == 1)
        {
            if(Mode == 1)
            {
                Mode = 0;
                DS1302_SetTime();
            }
            else
            {
            Mode = 1;
            TimeSet_Select = 0;
            }
        }
        switch(Mode)
        {
            case 0: TimeShow(); break;
            case 1: TimeSet(); break;
        }
    }
}



void Timer0_Isr(void) interrupt 1
{
    static unsigned int T0_count = 0;

	TL0 = 0x66;	
	TH0 = 0xFC;

    T0_count++;
    if(T0_count >= 500)
    {
        T0_count = 0;
        TimeSet_Flag = !TimeSet_Flag;
        //!是逻辑取反，~为按位取反，这里只需要逻辑取反
    }
}