#include <STC89C5xRC.H>
#include"Delay.h"

sbit RCK = P3^5;
//位声明重新声明IO，方便使用（避免重定义，以CLK位名）
sbit SCK = P3^6;
sbit SER = P3^4;

#define MATRIX_LED_PORT   P0

/**
 * @brief 74HC595写入一个字节
 * @param Byte 要写入的字节
 * @retval void 
 */

void _74HC595_WriteByte(unsigned char Byte)
{
    unsigned char i = 0;
    for(i = 0; i < 8; i++)
    {
    SER = Byte & (0x80 >> i);//1000 0000
    //SER为一位，赋值时非0即1，即赋值任何非0数，SER = 1
    //取出最高位（第8位是1，则Byte = 0x80，如果是1，则Byte = 0）

    SCK = 1;
    SCK = 0;
    }

    RCK = 1;
    //将数据移入IO进行输出
    RCK = 0;
}

/**
 * @brief Led点阵屏显示一列数据
 * 
 * @param Column 要选择的列，范围（0~7）
 * @param Data 选择列显示的数据，高位在上，1为亮，0为灭
 * @retval void
 */

void MatrixLED_ShowColmn(unsigned char Column, unsigned char Data)
{
    _74HC595_WriteByte(Data);//选择行
    MATRIX_LED_PORT = ~(0x80 >> Column);//选择列
    Delay(1);
    MATRIX_LED_PORT = 0xff;//位清零
}

void main()
{
    SCK = 0;
    RCK = 0;
    //时钟复位
    while(1)
    {   
        //位选时按列为单位
        MatrixLED_ShowColmn(0, 0x3c);
        MatrixLED_ShowColmn(1, 0x42);
        MatrixLED_ShowColmn(2, 0xa9);
        MatrixLED_ShowColmn(3, 0x85);
        MatrixLED_ShowColmn(4, 0x85);
        MatrixLED_ShowColmn(5, 0xa9);
        MatrixLED_ShowColmn(6, 0x42);
        MatrixLED_ShowColmn(7, 0x3c);
    }
}