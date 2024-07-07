#include <REGX52.H>
#include "UART.h"

void main(){
	P2 = 0xFF;
	Uart1_Init();
	while(1){}

}

// 中断服务子函数，中断号4产生后，进入中断函数
void UART_Rountine(void) interrupt 4{
	// 区分发送中断
	if (RI == 1){
		P2 = SBUF;  // 接受中断，读取接受数据
		RI = 0;  // 需要软件置位
		
		// 同时将数据发送回电脑端
		Uart_SendByte(SBUF);
	}
}