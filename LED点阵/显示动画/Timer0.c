#include <REGX52.H>

/*
    *  @brief  定时器0初始化，1毫秒 @11.0592
    *  @param  无
    *  @retval  无
*/
void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	// AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	
	// 手动添加 配置中断
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

/*
// 定时器0的中断函数模板
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
		P2_0 = ~P2_0;
	}
}  
*/