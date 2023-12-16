// #include<STC89C5xRC.H>

// unsigned char NixieTable[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// //0， 1， 2， 3， 4， 5， 6， 7， 8， 9对应的段码

// void NixieTube_Display(unsigned char location, unsigned char num)
// //分别传入显示位置、显示数字
// {
//     switch(location)
//     {
//         case 1:
//             P2_4 = 1;
//             P2_3 = 1;
//             P2_2 = 1;
//             break;
//         case 2:
//             P2_4 = 1;
//             P2_3 = 1;
//             P2_2 = 0;
//             break;
//         case 3:
//             P2_4 = 1;
//             P2_3 = 0;
//             P2_2 = 1;
//             break;
//         case 4:
//             P2_4 = 1;
//             P2_3 = 0;
//             P2_2 = 0;
//             break;
//         case 5:
//             P2_4 = 0;
//             P2_3 = 1;
//             P2_2 = 1;
//             break;
//         case 6:
//             P2_4 = 0;
//             P2_3 = 1;
//             P2_2 = 0;
//             break;
//         case 7:
//             P2_4 = 0;
//             P2_3 = 0;
//             P2_2 = 1;
//             break;
//         case 8:
//             P2_4 = 0;
//             P2_3 = 0;
//             P2_2 = 0;
//             break;
//     }
//     P0 =  NixieTable[num];
// }

// void main()
// {
//     NixieTube_Display(8, 0);
//     while(1)
//     {
        
//     }
// }



#include<STC89C5xRC.H>

void main()
{
    P2_4 = 1;
    P2_3 = 0;
    //此时LED3、4亮起（引脚冲突）
    P2_2 = 0;
    //控制74HC138

    P0 = 0x3F;
    //控制74HC245
    //第四个数码管显示6

    while(1)
    {
        
    }
}