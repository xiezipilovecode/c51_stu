#include <REGX52.H>
// 自定义延迟函数
#include <INTRINS.H>

// 自定义延迟函数，延迟指定时间
void Delay(unsigned int times)	//@11.0592MHz
{
	unsigned char data i, j;
	
	while(times--){
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main(){
	unsigned char LEDNum=0;
	
	while(1){
		if(P3_1 == 0){
			Delay(20);
			while(P3_1==0){
			}
			Delay(20);
			LEDNum++;
			
			P2 = ~LEDNum;
		}
	}
}