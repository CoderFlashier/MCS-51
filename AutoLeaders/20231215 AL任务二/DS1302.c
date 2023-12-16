#include <STC89C5xRC.H>
#include "MatrixKey.h"
#include "NixieTube_Display.h"

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


void DS1302_Init();
void DS1302_Write(unsigned char Command, unsigned char Data);
unsigned char DS1302_Read(unsigned char Command);
void DS1302_SetTime();
void DS1302_ReadTime();
unsigned char DEC_To_BCD(unsigned char DEC_Num);
unsigned char BCD_To_DEC(unsigned char BCD_Num);
void DS1302_TimeChange(unsigned char Change_Mode);



char DS1302_Time[2][3] = {{12, 0, 0}, {12, 0, 0}};
//分别用于计时、闹钟


void DS1302_Init()
//初始化DS1302
{
    DS1302_CE = 0;//使能
    DS1302_SCLK = 0;//串行时钟置0
}


void DS1302_Write(unsigned char Command, unsigned char Data)
//写入数据
{
    unsigned char i = 0;
    DS1302_CE = 1;//停止运行
    for(i = 0; i < 8; i++)
    {
        DS1302_IO = Command & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }

    for(i = 0; i < 8; i++)
    {
        DS1302_IO = Data & (0x01 << i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }

    DS1302_CE = 0;//恢复运行
    DS1302_SCLK = 0;
}


unsigned char DS1302_Read(unsigned char Command)
//读取当前时间
{
    unsigned char Data = 0x00;
    unsigned char i = 0;
    Command |= 0x01;//保证第一位置1
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
            //从最低位开始读取，应存到最低位
        }
    }

    DS1302_CE = 0;
    DS1302_SCLK = 0;

    DS1302_IO = 0;//这里需要将IO重置，否则读取的数据会在输入数据和ff之间横跳
    return Data;
}


void DS1302_SetTime()
//将时间写入DS1302
{
    DS1302_Write(DS1302_WP, 0x00);//关闭写保护
    DS1302_Write(DS1302_HOUR, DEC_To_BCD(DS1302_Time[0][0]));
    DS1302_Write(DS1302_MINUTE, DEC_To_BCD(DS1302_Time[0][1]));
    DS1302_Write(DS1302_SECOND, DEC_To_BCD(DS1302_Time[0][2]));
    DS1302_Write(DS1302_WP, 0x81);//打开写保护
}


void DS1302_ReadTime()
//读取当前时间
{
    unsigned char Temp = 0;

    Temp = DS1302_Read(DS1302_HOUR);
    DS1302_Time[0][0] = BCD_To_DEC(Temp);
    Temp = DS1302_Read(DS1302_MINUTE);
    DS1302_Time[0][1] = BCD_To_DEC(Temp);
    Temp = DS1302_Read(DS1302_SECOND);
    DS1302_Time[0][2] = BCD_To_DEC(Temp);
}



unsigned char DEC_To_BCD(unsigned char DEC_Num)
//十进制转BCD
{
    return DEC_Num / 10 * 16 + DEC_Num % 10;
}


unsigned char BCD_To_DEC(unsigned char BCD_Num)
{
    return BCD_Num / 16 * 10 + BCD_Num % 16;
}


void DS1302_TimeChange(unsigned char Change_Mode)
//Change_Mode为0时调整时钟，为1时调整闹钟
{
    static unsigned char Time_Select = 0;//保证变量不被删除，防止在每一次调用函数的时候都置0
    unsigned char Key_Num = 0;
    static unsigned char last_Key_num = 0;
    
    Key_Num = MatrixKey();
    if((Key_Num == 1 && last_Key_num == 0) || (Key_Num == 5 && last_Key_num == 0)) Time_Select = 0;
    if((Key_Num == 2 && last_Key_num == 0) || (Key_Num == 6 && last_Key_num == 0)) Time_Select = 1;
    if((Key_Num == 3 && last_Key_num == 0) || (Key_Num == 7 && last_Key_num == 0)) Time_Select = 2;


    switch(Time_Select)
    {
        case 0:
            NixieTube_DisplayTime(Change_Mode, 1);
            //合法性检查
            if(Key_Num == 1 && last_Key_num == 0)
            {
                DS1302_Time[Change_Mode][0]++;
                if(DS1302_Time[Change_Mode][0] > 23) DS1302_Time[Change_Mode][0] = 0;
            }
            if(Key_Num == 5 && last_Key_num == 0)
            {
                DS1302_Time[Change_Mode][0]--;
                if(DS1302_Time[Change_Mode][0] < 0) DS1302_Time[Change_Mode][0] = 23;
            }
            last_Key_num = Key_Num;
            break;
    

        case 1:
            NixieTube_DisplayTime(Change_Mode, 2);
            if(Key_Num == 2 && last_Key_num == 0)
            {
                DS1302_Time[Change_Mode][1]++;
                if(DS1302_Time[Change_Mode][1] > 59) DS1302_Time[Change_Mode][1] = 0;
            }
            if(Key_Num == 6 && last_Key_num == 0)
            {
                DS1302_Time[Change_Mode][1]--;
                if(DS1302_Time[Change_Mode][1] < 0) DS1302_Time[Change_Mode][1] = 59;
            }
            last_Key_num = Key_Num;
            break;
    
        case 2:
            NixieTube_DisplayTime(Change_Mode, 3);
            if(Key_Num == 3 && last_Key_num == 0)
            {
                DS1302_Time[Change_Mode][2]++;
                if(DS1302_Time[Change_Mode][2] > 59) DS1302_Time[Change_Mode][2] = 0;
            }
            if(Key_Num == 7 && last_Key_num == 0)
            {
                DS1302_Time[Change_Mode][2]--;
                if(DS1302_Time[Change_Mode][2] < 0) DS1302_Time[Change_Mode][2] = 59;
            }
            last_Key_num = Key_Num;
            break;

        default:
            last_Key_num = Key_Num;
    }
}


unsigned char Is_Clock_Alarm()
//判断闹钟是否响起
{
    unsigned char i = 0;
    for(i = 0; i < 3; i++)
    {
        if(DS1302_Time[0][i] != DS1302_Time[1][i]) return 0;
    }
    return 1;
}