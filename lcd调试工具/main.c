#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main(){
	unsigned int results = 0;  // 局部变量定义必须放在第一行
	LCD_Init();
//	LCD_ShowChar(1, 1, 'A');
	LCD_ShowString(2, 1, "Zei Ni Ma");
//	LCD_ShowNum(1, 11, 12345, 5);
//	LCD_ShowSignedNum();
//	LCD_ShowHexNum();
//	LCD_ShowBinNum();
	while(1){
		LCD_ShowNum(1, 1, results, 3);
		results++;
		Delay(500);
		
		if (results>60) results = 0;
	}
}