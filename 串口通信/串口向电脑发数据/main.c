#include <REGX52.H>
#include "Delay.h"
#include "UART.h"


void main(){
	unsigned char byte=0;
	// 初始化串口
	Uart1_Init();
	
	while(1){
		Uart_SendByte(byte);
		byte++;
		if (byte >= 0xFF)	byte=0;
		Delay(1000);
	}

}