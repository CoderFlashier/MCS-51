#include <STC89C5xRC.H>
#include"Delay.h"
#include "MatrixLED.h"

unsigned char code Animation[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                            0xFF, 0x10, 0x10, 0x10, 0xFF, 0x00, 0x1F, 0x15,
                            0x15, 0x1D, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x1F,
                            0x11, 0x11, 0x11, 0x1F, 0x00, 0x3D, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//显示的图像，在最前面加8位0，用于防止图像突然被切换，实现图像的连贯显示
//用code，将数据放入Flash

void main()
{
    unsigned char i = 0;
    unsigned char offset = 0;
    //偏移量
    unsigned char count = 0;
    MatrixLED_Init();
    while(1)
    {   
       for(i = 0; i < 8; i++)
       {
            MatrixLED_ShowColmn(i, Animation[i + offset]);
            //利用循环，实现一行语句点亮整个点阵屏
       }
       count++;
       if(count>10)
       //在一个状态扫描10次后，进入下一个状态（左移1位）
       {
            count = 0;
            offset++;
            //图像左移
            if(offset > 32)
            //完整显示一次图像后重置
            {
                offset = 0;
            }

       }
    }
}