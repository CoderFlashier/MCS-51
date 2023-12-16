#ifndef __DS1302_H__
#define __DS1302_H__

char DS1302_Time[][3];

void DS1302_Init();//初始化
void DS1302_SetTime();//设置时间
void DS1302_ReadTime();//读取时间
void DS1302_TimeChange(unsigned char Change_Mode);//调整时间
unsigned char Is_Clock_Alarm();//判断闹钟是否响起

#endif