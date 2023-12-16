#include<STC89C5xRC.H>
#include"Delay.h"
#include"Nixie_display.h"
//<>表示在安装目录寻找文件
//""表示在当前目录寻找文件


void main()
{
    while(1)
    {
        Delay(5000);
        NixieTube_Display(3, 3);
        Delay(5000);
        NixieTube_Display(4, 4);
    }
}