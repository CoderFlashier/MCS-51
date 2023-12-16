#ifndef __DS1302_H__
#define __DS1302_H__

char DS1302_Time[];
//数组和函数可以不加extern


void DS1302_Init();
void DS1302_WriteByte(unsigned char Command, unsigned char Data);
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_ReadTime();
void DS1302_SetTime();

#endif