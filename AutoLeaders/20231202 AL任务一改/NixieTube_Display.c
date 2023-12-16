#include "Delay.h"
#include<STC89C5xRC.H>

//0， 1， 2， 3， 4， 5， 6， 7， 8， 9, U, -对应的段码
unsigned char NixieTable[12] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x3E, 0x40};


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