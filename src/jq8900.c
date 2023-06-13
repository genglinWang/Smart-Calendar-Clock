#include "jq8900.h"

sbit sda = P1 ^ 5;

void Display_String(uchar line, uchar *string);
uchar key_scan();
uchar song;

// ��ʱ�Ӻ���
void Delay1500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 17;
	j = 31;
	do
	{
		while (--j);
	} while (--i);
}

// ��ʱ�Ӻ���
void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

// ��ʱ�Ӻ���
void Delay2ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 22;
	j = 128;
	do
	{
		while (--j);
	} while (--i);
}

// ��ʱ�Ӻ���
void Delay4ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 44;
	j = 4;
	do
	{
		while (--j);
	} while (--i);
}

// ��һ��ͨ����jq8900����ָ��
// ����ָ�� 0x11���ظ�����
// 0x13���������� 0x0a��������� 0x0b��ѡ��ȷ��
void SendData(uint addr) // �� �� �� ��
{
		int i = 0;
		EA = 0; //�� �� ʱ �� �� �� �� �� �� ֹ �� �� Ӱ �� ʱ �� 
		sda = 1;//�� ʼ �� ��
		Delay2ms();
		sda = 0; //�� ʼ �� �� �� 
		Delay4ms(); //�� �� �� ʱ �� �� Ҫ �� �� 2 m s �� �˲����� ʱ Ϊ 3 1 0 m s 
		for( i=0;i<8;i++) //�� �� 8 λ �� �� 
		{
				sda = 1;
				if(addr & 0x01) //3 : 1 �� ʾ �� �� λ 1 , ÿ ��λ �� �� �� �� �� �� ʾ 
				{
						Delay1500us();
						sda = 0 ;
						Delay500us();
				}
				else //1 �� 3 �� ʾ �� �� λ 0 , ÿ�� λ �� �� �� �� �� �� ʾ 
				{
						Delay500us();
						sda = 0;
						Delay1500us();
				}
				addr >>= 1;
		}
		sda = 1 ;
		EA = 1 ; //�� �� �� ��
}


// ѡ���Ӻ����������׸�����ʹ��jq8900�洢���汾�洢��sd����,��0000x.mp4����
// ������Ļ��ʾ��ͨ��ȫ�ֱ���song�洢������ţ�ͨ��senddata��song��ѡ�����š�
void Musicselect(void)
{
	uchar flag = 1, key;
	while(1)
	{
		Display_String(1,"ѡ������  03save");
		if (flag == 1)
		{
			Display_String(2,"1.ϲ����beyond +");
			Display_String(3,"2.ǧǧ�ڸ�      ");
			Display_String(4,"3.��ҹ��ʱ��    ");
		}
		else if (flag == 2)
		{
			Display_String(2,"1.ϲ����beyond  ");
			Display_String(3,"2.ǧǧ�ڸ�     +");
			Display_String(4,"3.��ҹ��ʱ��    ");
		}
		else if (flag == 3)
		{
			Display_String(2,"1.ϲ����beyond  ");
			Display_String(3,"2.ǧǧ�ڸ�      ");
			Display_String(4,"3.��ҹ��ʱ��   +");
		}
		else if (flag == 4)
		{
			Display_String(2,"2.ǧǧ�ڸ�      ");
			Display_String(3,"3.��ҹ��ʱ��    ");
			Display_String(4,"4.����         +");
		}
		else if (flag == 5)
		{
			Display_String(2,"3.��ҹ��ʱ��    ");
			Display_String(3,"4.����          ");
			Display_String(4,"5.��������     +");
		}
		else if (flag == 6)
		{
			Display_String(2,"4.����          ");
			Display_String(3,"5.��������      ");
			Display_String(4,"6.�質���     +");
		}
		
		key = key_scan();
		if (key == 2)
		{
			flag++;
			if(flag == 7)flag = 1;
		}
		else if (key == 3)
		{
			song = flag;
			break;
		}
	}
}

