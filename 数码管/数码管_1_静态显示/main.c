#include <REGX52.H>
// �Զ����ӳٺ���
#include <INTRINS.H>

unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// �Զ����ӳٺ������ӳ�ָ��ʱ��
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



// ���õ�ǰѡ���������Լ��������ʾ������
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
}



void main(){
	// ѡ��ָ���������
	Nixie(8, 1);	
	while(1){}
}