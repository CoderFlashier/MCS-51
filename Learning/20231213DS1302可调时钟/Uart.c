#include <STC89C5xRC.H>

/**
 * @brief 串口初始化
 * @param 无
 * @retval 无
 */


void Uart_Init(void)	//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;			//设置定时初始值
	TH1 = 0xFD;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}


// void Uart_Init()//4800bps@11.0592MHz
// //初始化寄存器
// {
//     SCON = 0x40;
//     PCON = 0;
//     //此处不需要配置中断

//     //配置定时器1
// 	TMOD &= 0x0F;       //TMOD高四位置0
// 	TMOD |= 0x20;       //串口需要用“8位自动重装”模式
//     TL1 = 0xFA;			//设置定时初始值
// 	TH1 = 0xFA;			//设置定时重载值
// 	ET1 = 0;			//禁止定时器中断
// 	TR1 = 1;			//定时器1开始计时
// }


/**
 * @brief 串口发送一个字节的数据
 * @param 一个字节的数据
 * @retval 无
 */


void Uart_SendByte(unsigned int Byte)
//发送数据
{
    SBUF = Byte;
    //将数据写入SBUF
    while(TI == 0);
    //当发送未完成，保持在函数内

    TI = 0;
    //重置TI
}