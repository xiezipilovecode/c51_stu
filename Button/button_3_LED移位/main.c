#include <REGX52.H>
// �Զ����ӳٺ���
#include <INTRINS.H>

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

void main(){
	unsigned char LEDNum=0;
	P2 = ~0x01;
	
	while(1){
		// ��������
		if (P3_1 == 0){
			Delay(20);
			while(P3_1==0){
			}  // �������
			Delay(20);
			LEDNum++;
			if (LEDNum>=8){
				LEDNum = 0;
			}
			P2 = ~(0x01 << LEDNum);
		}
		// ��������
		if (P3_0 == 0){
			Delay(20);
			while(P3_0==0){
			}  // �������
			Delay(20);
			
			if (LEDNum==0)	LEDNum=7;
			else LEDNum--;
			P2 = ~(0x01 << LEDNum);
		}
	}
}