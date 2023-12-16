#include <STC89C5xRC.H>
#include <INTRINS.H>
#include "Timer0.h"
#include "Inde_Key.h"

// void Timer0_init()
// //配置寄存器
// {
//     //TMOD = 0x01;
//     //0000 0001
//     //前四位为定时器1，不管；第五位为GATE，第六位为C/T，七、八位为M1、M0
//     //此处不可位寻址，只能整体赋值
//     //这样写有问题：在配置Timer1的时候会把Timer2的设置抹去

//     TMOD = TMOD & 0xF0;
//     //把TMOD的第四位清零而高四位不变（按位与：有0为0）
//     TMOD =  TMOD | 0x01;
//     //TMOD的最低位置一（按位或：有1为1）


//     //TCON可为寻址
//     TF0 = 0;
//     //清零
//     TR0 = 1;
//     TH0 = 64613 / 256;
//     TL0 = 64613 % 256;
//     //约921.65次为1ms，即初始化为65535 - 922 = 64613
//     //分别取高位和低位


//     //配置中断
//     ET0 = 1;
//     EA = 1;
//     PT0 = 0;
// }



// void Timer0_Init(void)		//1毫秒@11.0592MHz
// {
// 	AUXR &= 0x7F;			//定时器时钟12T模式
// 	TMOD &= 0xF0;			//设置定时器模式
// 	TMOD |= 0x01;			//设置定时器模式
// 	TL0 = 0x66;				//设置定时初始值
// 	TH0 = 0xFC;				//设置定时初始值
// 	TF0 = 0;				//清除TF0标志
// 	TR0 = 1;				//定时器0开始计时
// 	ET0 = 1;				//使能定时器0中断
//     EA = 1;//需要自己加
//     PT0 = 0;//同上
// }


unsigned char KeyNum = 0;
unsigned char LEDMode = 0;

void main()
{
    P2 = 0xFE;//点亮最低位LED
    Timer0_init();
    //初始化定时器，此时定时器开始运行
    //定时器的工作不需要单独执行，只需启动即可

    while(1)
    {
        KeyNum = Inde_Key();
        if(KeyNum)
        {
            if(KeyNum == 1)
            {
                LEDMode++;
                if(LEDMode == 2)
                {
                    LEDMode = 0;
                }
            }
        }

    }
}


void Timer0_Isr(void) interrupt 1
{
    static unsigned int T0_count = 0;
    //定义为静态局部变量，使变量在函数结束后仍保留

	TL0 = 0x66;				//设置定时初始值
    //这里比自己设置的多一位，因为自己算出来的64613 + 922 = 65535 不会溢出，要再加1才溢出

	TH0 = 0xFC;				//设置定时初始值

    T0_count++;
    if(T0_count >= 500)//间隔500ms
    {
        T0_count = 0;
        if(LEDMode == 0)
        {
            P2 = _crol_(P2, 1);
            //左移，当移到最高位时，回到第一位，是一个循环过程
            //属于INTRINS.H
        }
        if(LEDMode == 1)
        {
            P2 = _cror_(P2, 1);
            //右移
        }

    }
}


// //当产生中断时，会跳转到此函数执行，执行完后再回到原函数

// //计算中断次数
// void Timer0_Routime() interrupt 1
// {
//     TH0 = 64613 / 256;
//     TL0 = 64613 % 256;
//     //严格来讲这里需要再+1，否则会多算1ms
//     //重置计数器
//     T0_count++;
//     if(T0_count >= 1000)
//     //1000次中断为1s
//     {
//         T0_count = 0;
//         P20 = ~P20;
//     }
// }