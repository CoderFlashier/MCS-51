#include<INTRINS.H>
//用到了_nop_注意这里要加头文件
#include<STC89C5xRC.H>

void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;

    while(xms > 0)
    {
        _nop_();
	    i = 2;
	    j = 199;
	do
	{
		while (--j);
	} while (--i);

    xms--;
    }
}