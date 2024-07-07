#include <REGX52.H>

/*
    *  @brief  串口初始化
    *  @param
    *  @retval 
*/
void Uart1_Init(void)	//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率，允许接收中断
	// AUXR &= 0xBF;		//定时器时钟12T模式
	// AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	
	// 启动中断，表示1发送或者接受数据的中断
	EA = 1;
	ES = 1;
}

/*
    *  @brief  串口发送一个字节数据
    *  @param  一个字节的数据
    *  @retval 
*/
void Uart_SendByte(unsigned char byte){
	// 单片机发送数据
	SBUF = byte;
	while(TI==0){}  // 这里循环的作用用来检测是否发送所有的数据
	TI = 0;
}