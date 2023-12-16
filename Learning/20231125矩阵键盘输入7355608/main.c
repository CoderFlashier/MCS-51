#include <STC89C5xRC.H>
#include<string.h>
#include<stdio.h>
#include"Delay.h"
#include"MatrixKey.h"
#include"LCD1602.h"

char password[8] = {0};
//注意\n需要占一个位置
int count = 0;
int Keynum = 0;


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
            //判断是否输入
            {
                count++;
                if(count <= 7)
                {
                    switch(Keynum)
                    //通过按键向字符串中加入对应数字
                    {
                        case 1:strcat(password, "1");break;
                        case 2:strcat(password, "2");break;
                        case 3:strcat(password, "3");break;
                        case 4:strcat(password, "4");break;
                        case 5:strcat(password, "5");break;
                        case 6:strcat(password, "6");break;
                        case 7:strcat(password, "7");break;
                        case 8:strcat(password, "8");break;
                        case 9:strcat(password, "9");break;
                        case 10:strcat(password, "0");break;
                    }
                }
                LCD_ShowString(2, 1, password);
            }

            if(Keynum == 11)
            {
                if(strcmp(password, "7355608") == 0)
                //判断密码是否正确
                //玩cs玩的
                {
                    LCD_ShowString(1, 1, "                ");
                    LCD_ShowString(2, 1, "                ");
                    LCD_ShowString(1, 1, "Bomb has been");
                    LCD_ShowString(2, 1, "planted!");
                }
                else
                {
                    count = 0;
                    strcpy(password, "");
                    //重置字符串
                    LCD_ShowString(1, 13, "ERR");
                    LCD_ShowString(2, 1, "        ");
                }
            }

            if(Keynum == 12)
            {
                strcpy(password, "");
                LCD_ShowString(2, 1, "        ");
                count = 0;
            }
            
        }
        //LCD_ShowString(2, 1, password);
        //由于要显示文字，实时显示密码就不能放在这里了，否则在最后还是显示密码
    }
}



