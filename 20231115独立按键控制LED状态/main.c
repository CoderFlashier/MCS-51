#include<STC89C5xRC.H>

void Delay(unsigned int xms)	//@12.000MHz
{
	unsigned char data i, j;

	while(xms > 0)
    {
        i = 2;
	    j = 239;
	do
	{
		while (--j);
	} while (--i);
    xms--;
    }
}


void main()
{
    while(1)
    {
        if(P31 == 0)
        {
        Delay(20);
        // 按键消抖
        //while(P31 == 0);
        //如果不松手，就会一直在这个循环里面
        Delay(20);
        //松手检测
        P2_0 = ~P2_0;
        }
    }
}

