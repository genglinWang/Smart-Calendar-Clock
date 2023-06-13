# include <reg52.h>
#include "ds1302.h"
#include "bluetooth.h"

void Delay5000ms();
void Delay500ms();
uchar weather;
/*****************************************************************
*�����жϷ����ӳ���
*****************************************************************/
void Uart_Isr(void)  interrupt 4
{
	uchar Recv;
	if(RI==1)
	{
		RI=0;
		Recv = SBUF;
		switch(Recv)
		{
			//�յ���Ӧ�����ݶ������ս��д���
			case 1:blue2time(1, 6);break;
			case 2:blue2time(0, 6);break;
			
			case 3:blue2time(1, 4);break;
			case 4:blue2time(0, 4);break;
			
			case 5:blue2time(1, 3);break;
			case 6:blue2time(0, 3);break;
			
			case 7:blue2time(1, 2);break;
			case 8:blue2time(0, 2);break;
			
			case 9:blue2time(1, 1);break;
			case 10:blue2time(0, 1);break;
			
			case 11:blue2time(1, 0);break;
			case 12:blue2time(0, 0);break;
			
			//�������õ�һ����
			case 13:blue2clocktime(1, 6);break;
			case 14:blue2clocktime(0, 6);break;
			
			case 15:blue2clocktime(1, 4);break;
			case 16:blue2clocktime(0, 4);break;
			
			case 17:blue2clocktime(1, 3);break;
			case 18:blue2clocktime(0, 3);break;
			
			case 19:blue2clocktime(1, 2);break;
			case 20:blue2clocktime(0, 2);break;
			
			case 21:blue2clocktime(1, 1);break;
			case 22:blue2clocktime(0, 1);break;
			
			case 23:blue2clocktime(1, 0);break;
			case 24:blue2clocktime(0, 0);break;
		}
		if(Recv >= 25)weather = Recv;
		}
}
/*****************************************************************
*���ڳ�ʼ��
*****************************************************************/
void Uart_Init_blue(void)
{
  SCON = 0x50;         //��ʽ1 8λ���� ���յ�ַ����ֹ ����ʹ�� 0101 0000
	PCON = 0x00;         //�����ʲ�����
	TMOD = 0x20;         //T1,8λ�Զ���װ
	TH1 = 0xfd;	  				//������9600
	TL1 = 0xfd;
	EA   = 1;
	ES   = 1;
	TR1 = 1;            //����t1
}
// ��Ƭ���������ֻ����������ݡ������ڱ���������
void PostChar(uchar character)
{
	SBUF = character;
	while(!TI);
	TI = 0;
}
