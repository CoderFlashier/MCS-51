#ifndef __MATRIX_LED_H__
#define __MATRIX_LED_H__

void _74HC595_WriteByte(unsigned char Byte);
void MatrixLED_ShowColmn(unsigned char Column, unsigned char Data);
void MatrixLED_Init();

#endif