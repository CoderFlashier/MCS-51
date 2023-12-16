#include<STC89C5xRC.H>

/**
 * @brief 定时器0初始化，1ms @11.0592MHz
 * @param 无
 * @retval 无
 */

void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
    EA = 1;//需要自己加
    PT0 = 0;//同上
}


/*
void Timer0_Isr(void) interrupt 1
{
    static unsigned int T0_count = 0;
    //定义为静态局部变量，使变量在函数结束后仍保留

	TL0 = 0x66;				//设置定时初始值
    //这里比自己设置的多一位，因为自己算出来的64613 + 922 = 65535 不会溢出，要再加1才溢出

	TH0 = 0xFC;				//设置定时初始值

    T0_count++;
    if(T0_count >= 1000)
    {
        T0_count = 0;
        P20 = ~P20;
    }
}
*/
//不容易模块化的部分，放在此处作为模板