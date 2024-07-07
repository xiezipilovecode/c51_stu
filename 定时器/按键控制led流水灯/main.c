#include <REGX52.H>
#include "Timer0.h"
#include "key.h"
#include <INTRINS.h>  // 函数库，使用定义好的循环移位函数

//void Timer0_init(){
//	// 不可位寻址  -- 只能整体赋值
//	// 这里不能直接写TMOD = 0x01 这样影响其他的定时器，有以下两种方式
//	// TMOD |= 0x01;  // 0000 0001 定时器工作在模式0，使用或运算保持高四位不变
//	TMOD &= 0xF0;  // 低四位清零，高四位不变
//	TMOD |= 0x01;  // 最低位置为1，其余位保持不变
//	
//	// 可位寻址  --  可以为每一位单独赋值
//	// 这里配置TCON
//	TF0 = 0;  // 中断标志
//	TR0 = 1;  // 定时器T0运行控制位
//	// 计数器记数0-65535 每个一微秒计数器加一  总记数时间65535us  65ms
//	// 因此要计时一秒，需要进行一些设置修改
//	// 64535 到 65535 溢出差值为1000us -- 1ms，这样可以产生1ms计时
//	TH0 = 64535 / 256;  // 高位  取出高八位
//	TL0 = 64535 % 256;  // 低位  取出低八位
//	
//	// 配置中断
//	ET0 = 1;
//	EA = 1;
//	PT0 = 0;
//	

//}

unsigned char keyNum, LEDMode;


void main(){
	// 初始化定时器
	Timer0_init();
	P2 = 0xFE;  // 点亮最低位LED
	while(1){
		keyNum = Key();  // 获取独立按键键码
		
		if (keyNum == 1){
			LEDMode++;
			if (LEDMode >= 2) LEDMode=0;  // 移位模式
		}
//		switch (keyNum){
//			case 1: 
//				P2_0 = ~P2_0; 
//				break;
//			case 2: P2_1 = ~P2_1; break;
//			case 3: P2_2 = ~P2_2; break;
//			case 4: P2_3 = ~P2_3; break;
//		}
	
	}


}

// 定时器0的中断函数
void Timer0_Routine(void) interrupt 1{
	// 这里一毫秒跳转到中断
	static unsigned int T0Count;  // 使用static，函数执行结束不清零，静态局部变量
	
	// 重置一毫秒
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	
	// 这里实现循环移位
	if (T0Count >= 500){
		T0Count = 0;
		if (LEDMode == 0) P2 = _crol_(P2, 1);
		else P2 = _cror_(P2, 1);
	}
}  