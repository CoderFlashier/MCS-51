#include <STC89C5xRC.H>
#include "LCD1602.h"
#include "Uart.h"

//对端口重定义
sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;


#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82 
#define DS1302_HOUR 0x84 
#define DS1302_DATE 0x86
#define DS1302_MONTH 0x88
#define DS1302_DAY 0x8a
#define DS1302_YEAR 0x8c
#define DS1302_WP 0x8e


char DS1302_Time[] = {23, 12, 14, 20, 36, 4};
//年,月,日,时,分,秒,星期

void DS1302_Init()
//初始化
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

void DS1302_WriteByte(unsigned char Command, unsigned char Data)
//单字节写入
{   
    unsigned char i = 0;
    DS1302_CE = 1;
    for(i = 0; i < 8; i++)
    {
        DS1302_IO = Command & (0x01 << i);
        DS1302_SCLK = 1;
        //如果马上置0，时钟有可能反应不过来
        DS1302_SCLK = 0;
        //对运行速度快的单片机，可能需要加延时,这里不用
    }

    for(i = 0; i < 8; i++)
    {
        DS1302_CE = 1;
        DS1302_IO = Data & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }

    DS1302_CE = 0;
    DS1302_SCLK = 0;
}


unsigned char DS1302_ReadByte(unsigned char Command)
//单字节读取
{  
    unsigned char Data = 0x00;
    unsigned char i = 0;
    Command |= 0x01;//第一位置1
    DS1302_CE = 1;
    for(i = 0; i < 8; i++)
    {
        DS1302_CE = 1;
        DS1302_IO = Command & (0x01 << i);
        DS1302_SCLK = 0;
        DS1302_SCLK = 1;
        //在最后一个循环时为上升沿
    }


    for(i = 0; i < 8; i++)
    {
        DS1302_SCLK = 1;
        //重复置1，减去一个脉冲周期
        DS1302_SCLK = 0;
        //读取一位，同时使执行结束时为0
        if(DS1302_IO)
        {
            Data |= (0x01 << i);
            //读取的第一位为最低位
        }
    }

    DS1302_CE = 0;
    DS1302_SCLK = 0;
    DS1302_IO = 0;//这里需要将IO重置，否则读取的数据会在输入数据和ff之间横跳
    return Data;
}


void DS1302_SetTime()
{
    DS1302_WriteByte(DS1302_WP, 0x00);//关闭写保护
    DS1302_WriteByte(DS1302_YEAR, DS1302_Time[0] / 10 * 16 + DS1302_Time[0] % 10);//10转16进制
    DS1302_WriteByte(DS1302_MONTH, DS1302_Time[1] / 10 * 16 + DS1302_Time[1] % 10);
    DS1302_WriteByte(DS1302_DATE, DS1302_Time[2] / 10 * 16 + DS1302_Time[2] % 10);
    DS1302_WriteByte(DS1302_HOUR, DS1302_Time[3] / 10 * 16 + DS1302_Time[3] % 10);
    DS1302_WriteByte(DS1302_MINUTE, DS1302_Time[4] / 10 * 16 + DS1302_Time[4] % 10);
    DS1302_WriteByte(DS1302_SECOND, DS1302_Time[5] / 10 * 16 + DS1302_Time[5] % 10);
    DS1302_WriteByte(DS1302_DAY, DS1302_Time[6] / 10 * 16 + DS1302_Time[6] % 10);
    DS1302_WriteByte(DS1302_WP, 0x81);//打开写保护
}


void DS1302_ReadTime()
{
    unsigned char Temp = 0;
    Temp = DS1302_ReadByte(DS1302_YEAR);
    DS1302_Time[0] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_MONTH);
    DS1302_Time[1] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_DATE);
    DS1302_Time[2] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_HOUR);
    DS1302_Time[3] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_MINUTE);
    DS1302_Time[4] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_SECOND);
    DS1302_Time[5] = Temp / 16 * 10 + Temp % 16;
    Temp = DS1302_ReadByte(DS1302_DAY);
    DS1302_Time[6] = Temp / 16 * 10 + Temp % 16;
}