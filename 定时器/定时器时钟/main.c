#include <REGX52.H>
#include "LCD1602.h"
#include "Timer0.h"
#include "key.h"

unsigned char sec=0, min=0, hour=0;  // 初始时间定义
unsigned char keyNum;

void main(){
	LCD_Init();
	Timer0_Init();
	
	LCD_ShowString(1, 1, "Clock:");
	LCD_ShowString(2, 3, ":  :");
	LCD_ShowString(1, 15, "EN");
	
	while(1) {
		// 实时显示时间
		LCD_ShowNum(2, 1, hour, 2);
		LCD_ShowNum(2, 4, min, 2);
		LCD_ShowNum(2, 7, sec, 2);
		keyNum = Key();
		// 点击按钮，控制暂停和继续
		switch (keyNum){
			case 1:
				TR0 = ~TR0;
				LCD_ShowNum(2, 16, TR0, 1);
				break;                            
			case 2:
				sec=0; min=0; hour=0;
				break;
			default:
				break;
		}
	}
}	

void Timer0_Routine(void) interrupt 1{
	// 这里一毫秒跳转到中断
	static unsigned int T0Count;  // 使用static，函数执行结束不清零，静态局部变量
	
	// 重置一毫秒
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	
	// 一秒
	if (T0Count >= 1000){
		T0Count = 0;
		sec++;
		if (sec >= 60) {sec=0; min++;}
		if (min >= 60) {min=0; hour++;}
		if (hour >= 24) {hour=0;}
	}
}  