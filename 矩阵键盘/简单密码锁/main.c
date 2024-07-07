#include <REGX52.H>
#include "LCD1602.h"
#include "Matrixkey.h"

unsigned char keyNum;
unsigned int password, counts;  // 密码和记数

void main(){
	LCD_Init();
	LCD_ShowString(1, 1, "password");
	
	while(1){
		keyNum = matrix_key_scan();
//		if (keyNum){
//			LCD_ShowNum(2, 1, keyNum, 3);
//		}
		// 密码输入区域
		if (keyNum <= 10 && keyNum > 0){
			if (counts < 4){
				password *= 10;
				keyNum %= 10;
				password += keyNum;
				LCD_ShowNum(2, 1, password, 4);
				counts++;
			}
		}
		// 确认密码
		if (keyNum == 11){
			if (password == 1234){
				LCD_ShowString(1, 14, "OK!");
				counts = 0;
				password = 0;
				LCD_ShowNum(2, 1, password, 4);
			}
			else {
				LCD_ShowString(1, 14, "ERR");
				counts = 0;
				password = 0;
				LCD_ShowNum(2, 1, password, 4);
			}
		}
		// 清除密码
		if (keyNum == 12){
			counts = 0;
			password = 0;
			LCD_ShowNum(2, 1, password, 4);
		}
	}
}