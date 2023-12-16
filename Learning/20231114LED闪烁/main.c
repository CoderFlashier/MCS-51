#include <STC89C5xRC.H>
#include <INTRINS.H>

void Delay500ms(void)	//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	//需要添加头文件<INTRINS.H>
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main()
{
	while(1)
	{
		P2 = 0xFE;
		//点亮LED
		Delay500ms();
		//延时
		P2 = 0xFF;
		//熄灭LED
		Delay500ms();
	}
}

