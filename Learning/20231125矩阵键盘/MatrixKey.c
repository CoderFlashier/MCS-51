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


typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;

#define KEY_MATRIX_PORT	P1	//使用宏定义矩阵按键控制口		

#define SMG_A_DP_PORT	P0	//使用宏定义数码管段码口


void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}



// u8 key_matrix_flip_scan(void)
// {
// 	static u8 key_value=0;

// 	KEY_MATRIX_PORT=0x0f;//给所有行赋值0，列全为1
// 	if(KEY_MATRIX_PORT!=0x0f)//判断按键是否按下
// 	{
// 		delay_10us(1000);//消抖
// 		if(KEY_MATRIX_PORT!=0x0f)
// 		{
// 			//测试列
// 			KEY_MATRIX_PORT=0x0f;
// 			switch(KEY_MATRIX_PORT)//保存行为0，按键按下后的列值	
// 			{
// 				case 0x07: key_value=1;break;// 0000 0111
// 				case 0x0b: key_value=2;break;// 0000 1011
// 				case 0x0d: key_value=3;break;
// 				case 0x0e: key_value=4;break;
// 			}
// 			//测试行
// 			KEY_MATRIX_PORT=0xf0;
// 			switch(KEY_MATRIX_PORT)//保存列为0，按键按下后的键值	
// 			{
// 				case 0x70: key_value=key_value;break;
// 				case 0xb0: key_value=key_value+4;break;
// 				case 0xd0: key_value=key_value+8;break;
// 				case 0xe0: key_value=key_value+12;break;
// 			}
// 			while(KEY_MATRIX_PORT!=0xf0);//等待按键松开	
// 		}
// 	}
// 	//else
// 		//key_value=0;		
	
// 	return key_value;		
// }


// unsigned char juzhenjianpan(void){
// 	unsigned char a = 0;
// 	P1 = 0x0f;
// 	if(P1 != 0x0f)
// 	{
// 		Delay(20);
// 		if(P1 != 0x0f)
// 		{
// 			P1 = 0x0f;
// 			switch(P1)
// 			{
// 			case(0x07):a = 1;break;
// 			case(0x0b):a = 2;break;
// 			case(0x0d):a = 3;break;
// 			case(0x0e):a = 4;break;
// 			}
// 			P1 = 0xf0;
// 			switch(P1)
// 			{
// 			case(0x70):break;
// 			case(0xb0):a += 4;break;
// 			case(0xd0):a += 8;break;
// 			case(0xe0):a += 12;break;
// 			}
// 		}
// 		while(P1 != 0xf0);
// 		Delay(20);
// 	}
// 	return a;
// }