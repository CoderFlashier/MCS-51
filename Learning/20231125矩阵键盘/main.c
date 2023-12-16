#include <STC89C5xRC.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char Keynum = 0;

void main()
{
    LCD_Init();
    LCD_ShowString(1, 1, "Hello");
    while(1)
    {
        Keynum = MatrixKey2();
        //Keynum = juzhenjianpan();
        if(Keynum)
        {
            LCD_ShowNum(2, 1, Keynum, 2);
        }
    }
}


// unsigned char a;
// void main(){
// 	LCD_Init();	
// 	LCD_ShowChar(2, 1, 'a');
// 		while(1){
// 		a = juzhenjianpan();
// 		if(a){
// 			LCD_ShowNum(1,1,a,2);
// 		}
// 	}
// }