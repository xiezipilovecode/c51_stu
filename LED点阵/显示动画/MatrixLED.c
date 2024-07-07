#include <REGX52.H>
#include "Delay.h"

// 定义某一位
sbit RCK = P3^5;
sbit SCK = P3^6;
sbit SER = P3^4;

#define MATRIX_LED_PORT P0

void MatrixLED_Init(void){
	RCK = 0;
	SCK = 0;
}

/*
    *  @brief  74HC595写入一个字节数据
    *  @param  Byte为要写入的数据
    *  @retval 
*/
void _74HC595_WriteByte(unsigned char Byte){
	unsigned char i = 0;
	for (i=0; i<8; i++){  // 循环移位，移八次，这样就可以写入数据
		SER = Byte&(0x80>>i);
		SCK = 1;
		SCK = 0;
	}
	// 最后送出八位数据
	RCK = 1;
	RCK = 0;
}

/*
    *  @brief  LED点阵显示一列数据，显示指定列的数据
	*  @param  指定要选择的列，范围为0~8， Data为要显示的数据，高位在上
    *  @retval 
*/
void MatrixLED_ShowColumn(unsigned char Column, Data){
	_74HC595_WriteByte(Data);  // 选中指定的行
	// 段选，位选，延时，位清零
	MATRIX_LED_PORT = ~(0x80 >> Column);  // 选中指定的列  未选
	Delay(1);  // 延迟
	MATRIX_LED_PORT = 0xFF;  // 位清零
}