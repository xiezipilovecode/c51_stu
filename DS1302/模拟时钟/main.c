#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#inlcude "Key.h"
#include "Timer0.h"

unsigned char second;
unsigned char KeyNum;  // 当前按钮
unsigned char Mode=0;
unsigned char TimeSelect=0;  // 当前要设置的时间
unsigned char TimeSelectFlashFlag;  // 时间设置显示标志位

// 显示当前时间
void Show_Time(){
	unsigned char i;
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

// 设置当前时间
void Set_Time(){
	unsigned char i;
	
	// 2用来调整需要设置的时间
	if (KeyNum == 2){
		TimeSelect++;
		TimeSelect %= 6;  // 设置当前需要设置的时间
		// LCD_ShowNum(2, 13, TimeSelect, 2);
	}
	// 按键3用来加
	if (KeyNum == 3){
		// 这里进行越界判断
		DSl302_Time[TimeSelect]++;
		if (DSl302_Time[0] > 99) DSl302_Time[0] = 0;  // 年
		if (DSl302_Time[1] > 12)	DSl302_Time[1] = 1;  // 月
		
		if (DSl302_Time[1]==1 || DSl302_Time[1]==3 || DSl302_Time[1]==5 || DSl302_Time[1]==7
			|| DSl302_Time[1]==8 || DSl302_Time[1]==10 || DSl302_Time[1]==12){
				if (DSl302_Time[2] > 31) DSl302_Time[2] = 1;
			}
		else if (DSl302_Time[1]==4 || DSl302_Time[1]==6 || DSl302_Time[1]==9 || DSl302_Time[1]==11){
			if (DSl302_Time[2] > 30) DSl302_Time[2] = 1;
		}
		else{
			// 二月特殊情况
			if (DSl302_Time[0] % 4 == 0){
				if (DSl302_Time[2] > 29) DSl302_Time[2] = 1;
			}
			else{
				if (DSl302_Time[2] > 28) DSl302_Time[2] = 1;
			}
		}
		if (DSl302_Time[3] > 23)	DSl302_Time[3] = 0;  // 小时
		if (DSl302_Time[4] > 59) DSl302_Time[4] = 0;  // 分钟
		if (DSl302_Time[5] > 59)	DSl302_Time[5] = 0;  // 秒
	}
	// 按键4用来减
	if (KeyNum == 4){
		DSl302_Time[TimeSelect]--;
		if (DSl302_Time[0] < 0) DSl302_Time[0] = 99;  // 年
		if (DSl302_Time[1] < 1)	DSl302_Time[1] = 12;  // 月
		if (DSl302_Time[1]==1 || DSl302_Time[1]==3 || DSl302_Time[1]==5 || DSl302_Time[1]==7
			|| DSl302_Time[1]==8 || DSl302_Time[1]==10 || DSl302_Time[1]==12){
				if (DSl302_Time[2] < 1) DSl302_Time[2] = 31;
				// if (DSl302_Time[2] > 31) DSl302_Time[2] = 1;
			}
		else if (DSl302_Time[1]==4 || DSl302_Time[1]==6 || DSl302_Time[1]==9 || DSl302_Time[1]==11){
			if (DSl302_Time[2] < 1) DSl302_Time[2] = 30;
			// if (DSl302_Time[2] > 30) DSl302_Time[2] = 1;
		}
		else{
			// 二月特殊情况
			if (DSl302_Time[0] % 4 == 0){
				if (DSl302_Time[2] < 1) DSl302_Time[2] = 29;
				// if (DSl302_Time[2] > 29) DSl302_Time[2] = 1;
			}
			else{
				if (DSl302_Time[2] < 1) DSl302_Time[2] = 28;
				// if (DSl302_Time[2] > 28) DSl302_Time[2] = 1;
			}
		}
		if (DSl302_Time[3] < 0)	DSl302_Time[3] = 23;  // 小时
		if (DSl302_Time[4] < 0) DSl302_Time[4] = 59;  // 分钟
		if (DSl302_Time[5] < 0)	DSl302_Time[5] = 59;  // 秒
	}	
	
	// 更新显示，这里要进行闪烁显示
	// 闪烁当前选中位，因此只有选中当前位置，同时flash标志位为1，才可以进行闪烁
	// 第一行显示年月日
	for (i=0; i<3; ++i){
		if (TimeSelect==i && TimeSelectFlashFlag){LCD_ShowString(1, 3*i+1, "  ");}
		else {LCD_ShowNum(1, 3*i+1, DSl302_Time[i], 2);}
	}
	// 第二行显示时分秒、星期
	for (i=0; i<4; ++i){
		if (TimeSelect==i+3 && TimeSelectFlashFlag){LCD_ShowString(2, 3*i+1, "  ");}
		else {LCD_ShowNum(2, 3*i+1, DSl302_Time[i+3], 2);}
	}
	
	DS1302_SetTime();
}


void main(){
	LCD_Init();
	DS1302_Init();
	// 初始化定时器，进行一秒的闪烁
	Timer0_Init();
	DS1302_SetTime();  // 初始化当前时间
	LCD_ShowString(1, 0, "  -  -");
	LCD_ShowString(2, 0, "  :  :  -");
	
	while(1){
		KeyNum = Key();  // 获取当前按钮
		if (KeyNum){
			if (KeyNum == 1){
				if (!Mode) Mode=1;
				else {Mode=0; DS1302_SetTime(); }  // 重新设置时间
			}
		}
		
		if (Mode==0){
			Show_Time();
		}
		else{
			Set_Time();
		}
		
		
	}
}

// 定时器中断函数，进行闪烁
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
		TimeSelectFlashFlag = !TimeSelectFlashFlag;  // 逻辑取反
	}
}  