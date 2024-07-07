#include <REGX52.H>
#include "Delay.h"

/*
    *  @brief  获取独立按键键码
    *  @param  无
    *  @retval 按下按键的键码范围 0~4，无按键按下时，返回值为0
*/
unsigned char Key(){
	unsigned char keyNum = 0;
	
	// 独立按键检测
	if (P3_1==0) {Delay(20); while(P3_1 == 0); Delay(20); keyNum=1;}
	if (P3_0==0) {Delay(20); while(P3_0 == 0); Delay(20); keyNum=2;}
	if (P3_2==0) {Delay(20); while(P3_2 == 0); Delay(20); keyNum=3;}
	if (P3_3==0) {Delay(20); while(P3_3 == 0); Delay(20); keyNum=4;}
	
	return keyNum;
}