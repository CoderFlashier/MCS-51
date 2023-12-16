#include<STC89C5xRC.H>
#include"Delay.h"

/**
  * @brief 矩阵键盘读取按键键码
  * @param 无
  * @retval KeyNumber 按下按键的键码值
  * 如果按下按键不放，程序会停留在此函数，松手的一瞬间返回按键键码
  * 没有按键时，返回0
**/

unsigned char MatrixKey2()
{
    unsigned char Keynumber = 0;

    P1 = 0xff;
    P17 = 0;
    if(P13 == 0)
    {
        Keynumber = 1;
    }
    if(P12 == 0)
    {
        Keynumber = 2;
    }
    if(P11 == 0)
    {
        Keynumber = 3;
    }
    if(P10 == 0)
    {
        Keynumber = 4;
    }

    P1 = 0xff;
    P16 = 0;
    if(P13 == 0)
    {
        Keynumber = 5;
    }
    if(P12 == 0)
    {
        Keynumber = 6;
    }
    if(P11 == 0)
    {
        Keynumber = 7;
    }
    if(P10 == 0)
    {
        Keynumber = 8;
    }

    P1 = 0xff;
    P15 = 0;
    if(P13 == 0)
    {
        Keynumber = 9;
    }
    if(P12 == 0)
    {
        Keynumber = 10;
    }
    if(P11 == 0)
    {
        Keynumber = 11;
    }
    if(P10 == 0)
    {
        Keynumber = 12;
    }

    P1 = 0xff;
    P14 = 0;
    if(P13 == 0)
    {
        Keynumber = 13;
    }
    if(P12 == 0)
    {
        Keynumber = 14;
    }
    if(P11 == 0)
    {
        Keynumber = 15;
    }
    if(P10 == 0)
    {
        Keynumber = 16;
    }

    return Keynumber;
}