#include <REGX52.H>
// 自定义延迟函数
#include <INTRINS.H>

// 自定义延迟函数，延迟指定时间
void Delay(unsigned int times)	//@11.0592MHz
{
	unsigned char data i, j;
	
	while(times){
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		
		times--;
	}
}
// 这里要注意按键的抖动，干扰按键的抖动
/*
	按键消抖

*/

void main(){
	unsigned int flag = 0;
	
	while(1){
		if (P3_1==0){
			Delay(20);  // 按下按键抖动
			while(P3_1==0){}  // 按下按键的时候为低电平，不进行操作，松开的时候才进行操作
			Delay(20);  // 松开按键抖动
				
			P2_0 = ~P2_0;
		}
	}
}
		
//		if (P3_3 == 0){
//			flag = ~flag;
//		}
//		if (flag){
//			P2_0 = 0;
//		}
//		else P2_0 = 1;