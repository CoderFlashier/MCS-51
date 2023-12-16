#include <STC89C5xRC.H>
#include"LCD1602.h"
#include"Delay.h"

// void main()
// {
//     LCD_Init();
//     //初始化
//     LCD_ShowChar(1, 1, 'A');
//     //在一行一列显示'A'
//     LCD_ShowString(2, 1, "Hello,World!");
//     //显示字符串
//     LCD_ShowNum(1, 3, 52, 2);
//     //显示无符号数字，长度过短，高位不显示，长度过长，高位补0
//     LCD_ShowSignedNum(1, 6, -88, 2);
//     //这里设定显示的位数不包括负号
//     LCD_ShowHexNum(2, 1, 0xC4, 2);
//     //显示16进制的数，后面显示的会把前面显示的覆盖
//     LCD_ShowBinNum(1, 7, 0xA0, 8);
//     //显示二进制数字
//     while(1)
//     {
//     }
// }


int num = 0;

void main()
{
    LCD_Init();
    while (1)
    {
        num++;
        Delay(1000);
        LCD_ShowNum(1, 1, num, 2);
    }
    
}