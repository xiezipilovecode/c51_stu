#include <INTRINS.H>

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
