#include <reg51.h>
#include <string.h>
#include <stdio.h>

/*
Uart_Init:���ڳ�ʼ������
����:��
����:��
*/
void Uart_Init(void)
{
	TL1=0xfa;	//��11.0592MHz�����£����ò�����9600��������ʽ2
	TH1=0xfa;
	TMOD=0x20;
	SCON=0x50;	//���ڹ�����ʽ1���������
	PCON=0x80;
	EA=0;
	REN=1;
	TI=0;		//�����жϱ�־λ
	RI=0;		//�����жϱ�־λ
	TR1=1;		//��ʱ��1���������ʷ�����
}

/*
Putchar:���ڷ���1���ַ��ײ�������úú�����ñ�׼C����printf��������
����:�Ƿ�ִ�гɹ�
����:c ���͵��ַ�
*/
char putchar(char c)
{
	TI=0;
	SBUF=c;
	while(TI==0);
	return 1;
}
/*
Delay_ms:�ӳ�1ms�������Ǿ�ȷ��
����:��
����:x ���ٸ�1ms
*/
void Delay_ms(int x)
{
	volatile int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<5000;j++);
	}
}

/*
main:������ ����ѭ������"��Һ�"
����:��
����:��
*/
void main(void)
{
	Uart_Init();//���ڳ�ʼ��
	while(1)
	{
		printf("��Һ�");		//�������"��Һ�"
		Delay_ms(5000);		//�ӳ�5��
	}
}


