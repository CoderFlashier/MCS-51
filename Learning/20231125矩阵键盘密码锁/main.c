#include <STC89C5xRC.H>
#include "Delay.h"
#include "LCD1602.h"
#include"MatrixKey.h"

unsigned char Keynum = 0;
unsigned int Password = 0;
//0~65535, 定义4位密码即可
unsigned char count = 0;

void main()
{
    LCD_Init();
    LCD_ShowString(1, 1, "Password:");
    while(1)
    {
        Keynum = MatrixKey();
        if(Keynum)
        {
            if(Keynum <= 10)
            //如果按下的按键为S1~S10，输入密码
            {
                count++;
                //计算输入次数

                if(count <= 4)
                {
                    Password *= 10;
                    //上一位密码左移
                    Password += Keynum % 10;
                    //1-9得到原来的数，10取0
                    //获取一位密码
                }
            }
            if(Keynum == 11)
            //S11被按下，表示确认
            {
                if(Password == 1234)
                {
                    LCD_ShowString(1, 13, "OK ");
                    //密码正确
                }
                else
                {
                    LCD_ShowString(1, 13, "err");
                    Password = 0;
                    //重置状态
                    count = 0;
                }               
            }

            if(Keynum == 12)
            //S12按下，取消，即清空
            {
                Password = 0;
                count = 0;
            }

            LCD_ShowNum(2, 1, Password, 4);
            //更新显示
        }
    }
}