#include <STC89C5xRC.H>

void main()
{
	//P2 = 0xfe;
	P2_0 = 1;
	
	while(1)
	{
			if(P31 == 0 || P30 == 0)
	{
		P2_0 = 0;
	}
	else
	{
		P2_0 = 1;
	}
	}
}
