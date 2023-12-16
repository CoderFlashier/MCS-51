#include <STC89C5xRC.H>
#include "Delay.h"

/**
 * @brief 获取独立按键键码
 * @param 无
 * @return 按下按键的键码0~4（unsigned char），无按键按下时为0 
 */


unsigned char Inde_Key()
{
    unsigned char KeyNumber = 0;

    if(P31 == 0 || P30 == 0 || P32 == 0 || P33 == 0)
    {
        Delay(5);
        if(P31 == 0)
            KeyNumber = 1;
        if(P30 == 0)
            KeyNumber = 2;
        if(P32 == 0)
            KeyNumber = 3;
        if(P33 == 0)
            KeyNumber = 4;

        while(P31 == 0 || P30 == 0 || P32 == 0 || P33 == 0);
        Delay(5);
    }

    return KeyNumber;
}