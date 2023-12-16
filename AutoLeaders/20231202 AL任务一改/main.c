#include <STC89C5xRC.H>
#include"Delay.h"
#include"NixieTube_Display.h"

unsigned char Key_input();
void Mode1();
void Mode2();
void Mode3();
void Mode4();

unsigned if_mode_changed = 0;

unsigned char mode_mark = 0;
unsigned char Keynumber = 0;
unsigned char Keynumber_L = 0;

unsigned char m4_a = 0;

void main()
{    
    while(1)
    {
        Keynumber = Key_input();

    if(Keynumber != 0)
    {
        if(Keynumber == 1 && Keynumber_L == 0) mode_mark = 1;
        if(Keynumber == 2 && Keynumber_L == 0) mode_mark = 2;
        if(Keynumber == 3 && Keynumber_L == 0) mode_mark = 3;
        if(Keynumber == 4 && Keynumber_L == 0)
        {
            mode_mark = 4;
            m4_a = 1;
        }
    }
    Keynumber_L = Keynumber;

    switch (mode_mark)
    {
        case 1: Mode1(); break;
        case 2: Mode2(); break;
        case 3: Mode3(); break;
        case 4: Mode4(); break;
    }
    }
}


unsigned char Key_input()
{
    unsigned char Keynum = 0;
    if(P31 == 0 || P30 == 0 || P32 == 0 || P33 == 0)
    {
        Delay(5);
        if(P31 == 0)
            Keynum = 1;
        if(P30 == 0)
            Keynum = 2;
        if(P32 == 0)
            Keynum = 3;
        if(P33 == 0)
            Keynum = 4;
    }
    return Keynum;
}


void Mode1()
{
    if(if_mode_changed != 1)
    {
        if_mode_changed = 1;
    }
    NixieTube_Display(1, 10);
    NixieTube_Display(2, 1);
    NixieTube_Display(7, 0);
    NixieTube_Display(8, 1);
}


unsigned char S_count2 = 0;
unsigned char num2 = 0;

void Mode2()
{   

    if(if_mode_changed != 2)
    {
        if_mode_changed = 2;
        num2 = 0;
    }
    NixieTube_Display(1, 10);
    NixieTube_Display(2, 2);
    S_count2++;
    if(S_count2 == 230)
    {
        if(num2 == 10)
        {
            num2 = -1;
        }
        num2++;
        S_count2 = 0;
    }
    if(num2 <= 9)
    {
        NixieTube_Display(7, 0);
        NixieTube_Display(8, num2);
    }
    if(num2 == 10)
    {
        NixieTube_Display(7, 1);
        NixieTube_Display(8, 0);
    }
}


unsigned char S_count3 = 0;
unsigned char mark3 = 0;

void Mode3()
{
    if(if_mode_changed != 3)
    {
        if_mode_changed = 3;
        S_count3 = 0;
    }

    NixieTube_Display(1, 10);
    NixieTube_Display(2, 3);
    NixieTube_Display(7, 0);
    NixieTube_Display(8, 3);
    S_count3++;
    if(S_count3 == 100)
    {
        mark3++;
        S_count3 = 0;
    }
    if(mark3 % 2 == 0)
    {
        NixieTube_Display(5, 11);
        NixieTube_Display(6, 11);
    }
    if(mark3 % 2 == 1)
    {
        ;
    }
}


unsigned char num4 = 0;

void Mode4()
{
    if(if_mode_changed != 4)
    {
        if_mode_changed = 4;
        num4 = 0;
        m4_a = 0;
    }
    if(m4_a == 1)
    {
        num4++;
        m4_a = 0;
    }
    NixieTube_Display(1, 10);
    NixieTube_Display(2, 4);
    if(num4 == 10)
    {
        num4 = 0;
    }
    NixieTube_Display(7, num4);
    NixieTube_Display(8, num4);
}