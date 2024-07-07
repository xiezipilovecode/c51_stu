#include <REGX52.H>
#include "LCD1602.h"
#include "Matrixkey.h"

unsigned char keyNum;

void main(){
	LCD_Init();
	LCD_ShowString(1, 1, "MATRIX_KEY");
	
	while(1){
		// 这里获取按键的值，然后进行显示
		keyNum = matrix_key_scan();
		if(keyNum){
			LCD_ShowNum(2, 1, keyNum, 2);
		}
	}
}