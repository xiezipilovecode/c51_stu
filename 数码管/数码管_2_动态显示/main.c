#include <REGX52.H>
#include <INTRINS.H>

// 数码管显示的数字
unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void Delay(unsigned int times);

void Nixie(unsigned char Location, Number){
	switch(Location){
		case 1: P2_4=1, P2_3=1; P2_2=1; break;
		case 2: P2_4=1, P2_3=1; P2_2=0; break;
		case 3: P2_4=1, P2_3=0; P2_2=1; break;
		case 4: P2_4=1, P2_3=0; P2_2=0; break;
		case 5: P2_4=0, P2_3=1; P2_2=1; break;
		case 6: P2_4=0, P2_3=1; P2_2=0; break;
		case 7: P2_4=0, P2_3=0; P2_2=1; break;
		case 8: P2_4=0, P2_3=0; P2_2=0; break;
	}
	P0 = NixieTable[Number];
	// 这里进行消隐
	Delay(1);
	P0 = 0x00;
}

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
	while(1){
		Nixie(1, 1);
		// Delay(1);
		Nixie(2, 2);
		// Delay(1);
		Nixie(3, 3);
		// Delay(1);
		Nixie(4, 4);
		Nixie(5, 5);
		Nixie(6, 6);
		Nixie(7, 7);
		Nixie(8, 8);	
	}

}