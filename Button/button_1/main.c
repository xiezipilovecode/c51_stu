#include <REGX52.H>
// �Զ����ӳٺ���
#include <INTRINS.H>

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
// ����Ҫע�ⰴ���Ķ��������Ű����Ķ���
/*
	��������

*/

void main(){
	unsigned int flag = 0;
	
	while(1){
		if (P3_1==0){
			Delay(20);  // ���°�������
			while(P3_1==0){}  // ���°�����ʱ��Ϊ�͵�ƽ�������в������ɿ���ʱ��Ž��в���
			Delay(20);  // �ɿ���������
				
			P2_0 = ~P2_0;
		}
	}
}
		
//		if (P3_3 == 0){
//			flag = ~flag;
//		}
//		if (flag){
//			P2_0 = 0;
//		}
//		else P2_0 = 1;