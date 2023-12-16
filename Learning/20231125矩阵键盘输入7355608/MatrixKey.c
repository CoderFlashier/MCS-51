#include<STC89C5xRC.H>
#include"Delay.h"

/**
  * @brief 矩阵键盘读取按键键码
  * @param 无
  * @retval KeyNumber 按下按键的键码值
  * 如果按下按键不放，程序会停留在此函数，松手的一瞬间返回按键键码
  * 没有按键时，返回0
**/

unsigned char MatrixKey()
{
    unsigned char KeyNumber = 0;

    P1 = 0xff;
    P13 = 0;
    //除了P13以外全部置1
    if(P17 == 0)
    {
        Delay(20);
        while(P17 == 0);
        KeyNumber = 1;
    }
      if(P16 == 0)
    {
        Delay(20);
        while(P16 == 0);
        KeyNumber = 5;
    }
      if(P15 == 0)
    {
        Delay(20);
        while(P15 == 0);
        KeyNumber = 9;
    }
      if(P14 == 0)
    {
        Delay(20);
        while(P14 == 0);
        KeyNumber = 13;
    }
    //扫描第一列

    P1 = 0xff;
    P12 = 0;
    if(P17 == 0)
    {
        Delay(20);
        while(P17 == 0);
        KeyNumber = 2;
    }
      if(P16 == 0)
    {
        Delay(20);
        while(P16 == 0);
        KeyNumber = 6;
    }
      if(P15 == 0)
    {
        Delay(20);
        while(P15 == 0);
        KeyNumber = 10;
    }
      if(P14 == 0)
    {
        Delay(20);
        while(P14 == 0);
        KeyNumber = 14;
    }

    P1 = 0xff;
    P11 = 0;
    if(P17 == 0)
    {
        Delay(20);
        while(P17 == 0);
        KeyNumber = 3;
    }
      if(P16 == 0)
    {
        Delay(20);
        while(P16 == 0);
        KeyNumber = 7;
    }
      if(P15 == 0)
    {
        Delay(20);
        while(P15 == 0);
        KeyNumber = 11;
    }
      if(P14 == 0)
    {
        Delay(20);
        while(P14 == 0);
        KeyNumber = 15;
    }

    P1 = 0xff;
    P10 = 0;
    if(P17 == 0)
    {
        Delay(20);
        while(P17 == 0);
        KeyNumber = 4;
    }
      if(P16 == 0)
    {
        Delay(20);
        while(P16 == 0);
        KeyNumber = 8;
    }
      if(P15 == 0)
    {
        Delay(20);
        while(P15 == 0);
        KeyNumber = 12;
    }
      if(P14 == 0)
    {
        Delay(20);
        while(P14 == 0);
        KeyNumber = 16;
    }

    return KeyNumber;
}