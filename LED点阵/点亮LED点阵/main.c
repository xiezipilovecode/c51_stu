#include <REGX52.H>
#include "MatrixLED.h"
#include "Delay.h"

unsigned char plot_data[] = {0x3c, 0x42, 0xA9, 0x85, 0x85, 0xA9, 0x42, 0x3c};  // 这里是笑脸

void main(){
	unsigned char i;
	MatrixLED_Init();
	
	while (1){
		for (i=0; i<8; ++i){
			// 这里按照列进行扫描
			MatrixLED_ShowColumn(i, plot_data[i]);  // 显示
		}
	}
}