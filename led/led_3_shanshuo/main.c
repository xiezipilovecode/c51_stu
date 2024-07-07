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


// �Զ����ӳٺ������ӳ�ָ��ʱ��
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



void main(){
	unsigned char data i;
	P2 = 0xFE;  // 1111 1110
	
	for (i=0;i<8;i++){
		Delay(500);
		P2 = P2 << 1;  // ����һλ��1111 1100 
		// �������һλҪ���1 1111 1101
		P2 = P2 | 0x01;  // 1111 1100 | 0000 0001  -- 1111 1101  ÿ�������һλ����0��Ϊ1
	}

}