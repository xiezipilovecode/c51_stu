#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"

unsigned char second;

void main(){
	unsigned char i;
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();  // 初始化当前时间
	
	while(1){
		// 读取时间然后进行显示
		DS1302_ReadTime();
		// 第一行显示年月日
		for (i=0; i<3; ++i){
			LCD_ShowNum(1, 3*i+1, DSl302_Time[i], 2);
		}
		// 第二行显示时分秒、星期
		for (i=0; i<4; ++i){
			LCD_ShowNum(2, 3*i+1, DSl302_Time[i+3], 2);
		}
	}
	
	
}