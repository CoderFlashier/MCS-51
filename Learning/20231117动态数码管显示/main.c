#include<STC89C5xRC.H>

unsigned char NixieTable[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void NixieTube_Display(unsigned char location, unsigned char num)
{
    switch(location)
    {
        case 1:
            P2_4 = 1;
            P2_3 = 1;
            P2_2 = 1;
            break;
        case 2:
            P2_4 = 1;
            P2_3 = 1;
            P2_2 = 0;
            break;
        case 3:
            P2_4 = 1;
            P2_3 = 0;
            P2_2 = 1;
            break;
        case 4:
            P2_4 = 1;
            P2_3 = 0;
            P2_2 = 0;
            break;
        case 5:
            P2_4 = 0;
            P2_3 = 1;
            P2_2 = 1;
            break;
        case 6:
            P2_4 = 0;
            P2_3 = 1;
            P2_2 = 0;
            break;
        case 7:
            P2_4 = 0;
            P2_3 = 0;
            P2_2 = 1;
            break;
        case 8:
            P2_4 = 0;
            P2_3 = 0;
            P2_2 = 0;
            break;
    }
    P0 =  NixieTable[num];
    Delay(1);
    //让数码管稳定显示，否则亮度会变低
    P0 = 0x00;
    //清零
}

void main()
{
    NixieTube_Display(8, 0);
    while(1)
    {
        NixieTube_Display(1, 1);
        //Delay(500);
        NixieTube_Display(2, 2);
        //Delay(500);
        NixieTube_Display(3, 3);
        //Delay(500);
        //让数码管同时显示多个数字实际上就是数码管在不断扫描，可以通过延时函数来体现
    }
}