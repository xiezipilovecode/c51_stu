#include <REGX52.H>
#include <INTRINS.H>

void Delay500ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}



void main(){
	int lighting = 0xaa;  // 1010 1010
	int close = 0xFF; //
	
	while(1){
		P2 = lighting;
		Delay500ms();
		P2 = close;
		Delay500ms();
	}
}
