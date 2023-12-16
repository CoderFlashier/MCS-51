#include <STC89C5xRC.H>
#include "Delay.h"

unsigned char NixieTable[12] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x3E, 0x40};
//0， 1， 2， 3， 4， 5， 6， 7， 8， 9, U, -对应的段码

void NixieTube_Display(unsigned char location, unsigned char num)
//分别传入显示位置、显示内容
{
    switch(location)
    //选择显示位置
    {
        case 1:
            P2_4 = 1;
            P2_3 = 1;
            P2_2 = 1;
            break;

        case 2:
            P2_4 = 1;
            P2_3 = 1;
            P2_2 = 0;
            break;

        case 3:
            P2_4 = 1;
            P2_3 = 0;
            P2_2 = 1;
            break;

        case 4:
            P2_4 = 1;
            P2_3 = 0;
            P2_2 = 0;
            break;

        case 5:
            P2_4 = 0;
            P2_3 = 1;
            P2_2 = 1;
            break;

        case 6:
            P2_4 = 0;
            P2_3 = 1;
            P2_2 = 0;
            break;

        case 7:
            P2_4 = 0;
            P2_3 = 0;
            P2_2 = 1;
            break;

        case 8:
            P2_4 = 0;
            P2_3 = 0;
            P2_2 = 0;
            break;
    }

    P0 =  NixieTable[num];
    Delay(1);
    //让数码管稳定显示，否则亮度会变低
    //Delay写成了一个通用延时函数放在头文件了
    //注意STC89C52RC的晶振频率为11.0592MHz，在创建延时函数时应注意选择
    P0 = 0x00;
    //清零
}

unsigned char Keynum = 0;

unsigned char Key_input()
{
    Keynum = 0;
    if(P31 == 0 || P30 == 0 || P32 == 0 || P33 == 0)
    {
        Delay(5);
        if(P31 == 0)
            Keynum = 1;
        if(P30 = 0)
            Keynum = 2;
        if(P32 == 0)
            Keynum = 3;
        if(P33 == 0)
            Keynum = 4;
    }

    return Keynum;
}

void main()
{
    //用于标记当前运行模式
    int mark = 0;
    
    //用于标记模式三中，5、6号数码管是否显示
    int mark2 = 0;

    //用于标记模式四是第一次切换还是增加数字
    int mark3 = 1;

    //用于模式二的计时
    int index1 = 0;

    //用于模式三的计时
    int index2 = 0;

    int num1 = 0;  
    int num3 = 0;
    
    int D_num1 = 0;
    int D_num2 = 0;


    while(1)
    {
        // //这个地方如果把消抖和判断放在外面，由于每次扫描都要经过消抖的延时，扫描速度会变慢，所以写一个判断
        // //当有按键被按下时进入消抖和判断，如果没有，直接跳过这个过程，进行下一次扫描
        // if(P31 == 0 || P30 == 0 || P32 == 0 || P33 == 0)
        // //按键检测
        // {
        //     Delay(10);
        //     //消抖
        //     if(P31 == 0)
        //     {
        //         mark = 1;
        //         mark3 = 1;
        //         //当进入其它模式时，将mark3置1，表示当切换到模式四时，应显示0
        //     }

        //     if(P30 == 0)
        //     {
        //         mark = 2;
        //         num1 = 0;
        //         //时间归零
        //         index1 = 0;
        //         //计时器归零
        //         mark3 = 1;
        //     }

        //     if(P32 == 0)
        //     {
        //         mark = 3;
        //         index2 = 0;
        //         //计时器归零
        //         mark2 = 0;
        //         mark3 = 1;
        //     }

        //     if(P33 == 0)
        //     {
        //         mark = 4;
        //         //num3++;
        //         if(mark3 == 1)
        //         {
        //             num3 = 0;  
        //             mark3 = 0;
        //         }
        //         else
        //         {
        //             num3++;
        //         }
        //     }

        //     while(P31 == 0 || P30 == 0 || P32 == 0 || P33 == 0);
        //     Delay(10);
        // }

        unsigned char mark_n = 0;
        unsigned char last_keynum = 0;

        mark_n = Key_input();
        
        if(mark_n != 0)
        {
            if(last_keynum == 0 && mark_n == 1)
            {
                mark = 1;
                mark3 = 1;
            }

            if(last_keynum == 0 && mark_n == 2)
            {
                mark = 2;
                num1 = 0;
                index1 = 0;
                mark3 = 1;
            }

            if(last_keynum == 0 && mark_n == 3)
            {
                mark = 3;
                index2 = 0;
                mark2 = 0;
                mark3 = 1;
            }

            if(last_keynum == 0 && mark_n ==4)
            {
                mark = 4;
                if(mark3 == 1)
                {
                    num3 = 0;  
                    mark3 = 0;
                }
                else
                {
                    num3++;
                }
            }
        }


    
        switch (mark)
        {
            case 1:
                NixieTube_Display(1, 10);
                NixieTube_Display(2, 1);
                NixieTube_Display(7, 0);
                NixieTube_Display(8, 1);
                break;

            case 2:
                NixieTube_Display(1, 10);
                NixieTube_Display(2, 2);
                index1++;
                if(index1 == 230)
                //计算扫描次数
                {
                    if(num1 == 10)
                    {
                        num1 = -1;
                        //当计时到10秒时，设为-1，加上1为0
                    }
                    num1++;
                    index1 = 0;
                }
                if(num1 <= 9)
                {
                    NixieTube_Display(7, 0);
                    NixieTube_Display(8, num1);
                }
                if(num1 == 10)
                {
                    NixieTube_Display(7, 1);
                    NixieTube_Display(8, 0);
                }
                break;

            case 3:
                NixieTube_Display(1, 10);
                NixieTube_Display(2, 3);
                NixieTube_Display(7, 0);
                NixieTube_Display(8, 3);
                index2++;
                if(index2 == 100)
                //每0.5秒切换一次
                //这里的扫描更慢一点，所以设定的次数应该更低
                {
                    mark2++;
                    index2 = 0;
                }
                if(mark2 % 2 == 0)
                {
                    NixieTube_Display(5, 11);
                    NixieTube_Display(6, 11);
                }
                if(mark2 % 2 == 1)
                {
                    ;
                }
                break;

            case 4:
                NixieTube_Display(1, 10);
                NixieTube_Display(2, 4);
                // if(num3 <=9)
                // {
                //     NixieTube_Display(7, 0);
                //     NixieTube_Display(8, num3);
                // }
                // else if(num3 > 9 && num3 <= 99)
                // //两位数
                // {
                //     D_num1 = num3 / 10;
                //     D_num2 = num3 % 10;
                //     NixieTube_Display(7, D_num1);
                //     NixieTube_Display(8, D_num2);
                //     D_num1 = 0;
                //     D_num2 = 0;
                // }
                // else
                // //三位数归零
                // {
                //     num3 = 0;
                // }
                if(num3 == 10)
                {
                    num3 = 0;
                }
                NixieTube_Display(7, num3);
                NixieTube_Display(8, num3);
                break;
        }
        
    }
}