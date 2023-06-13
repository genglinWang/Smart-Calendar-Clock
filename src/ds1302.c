#include"ds1302.h"
#include"lcd.h"
sbit DSIO=P1^3;
sbit RST=P1^4;
sbit SCLK=P1^2;

//---DS1302д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//---DS1302ʱ�ӳ�ʼ��2016��5��7��������12��00��00�롣---//
//---�洢˳�������ʱ��������,�洢��ʽ����BCD��---//
uchar TIME[7] = {0x00, 0x00, 0x15, 0x06, 0x06, 0x00, 0x22};
//                0��   1��  2ʱ   3��   4��   5��   6��
uchar displayData[16];//��12864��ʾ�ĵ�һ��
uchar displayData2[16];//��12864��ʾ�ĵڶ���
uchar time1[16];
uchar time2[16];
uchar buffer[7];
uchar clocktime[7];
/*******************************************************************************
* �� �� ��         : Ds1302Write
* ��������		   : ��DS1302�����ַ+���ݣ�
* ��    ��         : addr,dat
* ��    ��         : ��
*******************************************************************************/
uchar key_scan();
void Display_String(uchar line, uchar *string);
void Delay5Ms(void);
void Add(uchar dateBCD, uchar symbol);

void Ds1302Write(uchar addr, uchar dat)
{
	uchar n;
	RST = 0;
	_nop_();

	SCLK = 0;//�Ƚ�SCLK�õ͵�ƽ��
	_nop_();
	RST = 1; //Ȼ��RST(CE)�øߵ�ƽ��
	_nop_();

	for (n=0; n<8; n++)//��ʼ���Ͱ�λ��ַ����
	{
		DSIO = addr & 0x01;//���ݴӵ�λ��ʼ����
		addr >>= 1;
		SCLK = 1;//������������ʱ��DS1302��ȡ����
		_nop_();
		SCLK = 0;
		_nop_();
	}
	for (n=0; n<8; n++)//д��8λ����
	{
		DSIO = dat & 0x01;
		dat >>= 1;
		SCLK = 1;//������������ʱ��DS1302��ȡ����
		_nop_();
		SCLK = 0;
		_nop_();
	}	
		 
	RST = 0;//�������ݽ���
	_nop_();
}

/*******************************************************************************
* �� �� ��         : Ds1302Read
* ��������		   : ��ȡһ����ַ������
* ��    ��         : addr
* ��    ��         : dat
*******************************************************************************/

uchar Ds1302Read(uchar addr)
{
	uchar n,dat,dat1;
	RST = 0;
	_nop_();

	SCLK = 0;//�Ƚ�SCLK�õ͵�ƽ��
	_nop_();
	RST = 1;//Ȼ��RST(CE)�øߵ�ƽ��
	_nop_();

	for(n=0; n<8; n++)//��ʼ���Ͱ�λ��ַ����
	{
		DSIO = addr & 0x01;//���ݴӵ�λ��ʼ����
		addr >>= 1;
		SCLK = 1;//������������ʱ��DS1302��ȡ����
		_nop_();
		SCLK = 0;//DS1302�½���ʱ����������
		_nop_();
	}
	_nop_();
	for(n=0; n<8; n++)//��ȡ8λ����
	{
		dat1 = DSIO;//�����λ��ʼ����
		dat = (dat>>1) | (dat1<<7);
		SCLK = 1;
		_nop_();
		SCLK = 0;//DS1302�½���ʱ����������
		_nop_();
	}

	RST = 0;
	_nop_();	//����ΪDS1302��λ���ȶ�ʱ��,����ġ�
	SCLK = 1;
	_nop_();
	DSIO = 0;
	_nop_();
	DSIO = 1;
	_nop_();
	return dat;	
}

/*******************************************************************************
* �� �� ��         : Ds1302Init
* ��������		   : ��ʼ��DS1302.
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Ds1302Init()
{
	uchar n;
	Ds1302Write(0x8E,0X00);		 //��ֹд���������ǹر�д��������
	for (n=0; n<7; n++)//д��7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		Ds1302Write(WRITE_RTC_ADDR[n], TIME[n]);	
	}
	Ds1302Write(0x8E,0x80);		 //��д��������
}

/*******************************************************************************
* �� �� ��         : Ds1302ReadTime
* ��������		   : ��ȡʱ����Ϣ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Ds1302ReadTime()
{
	uchar n;
	for (n=0; n<7; n++)//��ȡ7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
	}
		
}
//������ת��Ϊ����ʾ��12864�ϵ��ַ���
//void dataProcess(void)
void dataProcess(void)
{
	uchar i;
	Ds1302ReadTime();
	//��ĵ�1λ
	displayData[0] = '2';
	//��ĵ�2λ
	displayData[1] = '0';
	//��ĵ�3λ
	displayData[2] = TIME[6] / 16 + '0';
	//��ĵ�4λ
	displayData[3] = TIME[6] % 16 + '0';
	
	displayData[4] = '-';
	//�� ��λ
	displayData[5] = TIME[4] / 16 + '0';
	//�� βλ
	displayData[6] = TIME[4] % 16 + '0';
	
	displayData[7] = '-';
	//�� ��λ
	displayData[8] = TIME[3] / 16 + '0';
	//�� βλ
	displayData[9] = TIME[3] % 16 + '0';
	
	for (i=10; i<=15; i++)
	{
		displayData[i] = ' ';
	}
	///////////////////
	////����
	///////////////////
	
	//Сʱ ��λ
	displayData2[0] = TIME[2] / 16 + '0';
	//Сʱ βλ
	displayData2[1] = TIME[2] % 16 + '0';
	
	displayData2[2] = ':';
	//���� ��λ
	displayData2[3] = TIME[1] / 16 + '0';
	//���� βλ
	displayData2[4] = TIME[1] % 16 + '0';
	
	displayData2[5] = ':';
	//�� ��λ
	displayData2[6] = TIME[0] / 16 + '0';
	//�� βλ
	displayData2[7] = TIME[0] % 16 + '0';
	// �ָ�
	displayData2[8] = ' ';
	
	if (displayData2[0] == '0')
	{
		displayData2[9] = 'A';
	}
	else if (displayData2[0] == '1')
	{
		if (displayData2[1] >= '2')
		{
			displayData2[9] = 'P';
		}
		else
		{
			displayData2[9] = 'A';
		}
	}
	else
	{
		displayData2[9] = 'P';
	}
	

	displayData2[10] = 'M';
	for (i=11; i<=15; i++)
	{
		displayData2[i] = ' ';
	}
}


void dataProcess_new(void)
{
	uchar i;
	//��ĵ�1λ
	time1[0] = '2';
	//��ĵ�2λ
	time1[1] = '0';
	//��ĵ�3λ
	time1[2] = buffer[6] / 16 + '0';
	//��ĵ�4λ
	time1[3] = buffer[6] % 16 + '0';
	
	time1[4] = '-';
	//�� ��λ
	time1[5] = buffer[4] / 16 + '0';
	//�� βλ
	time1[6] = buffer[4] % 16 + '0';
	
	time1[7] = '-';
	//�� ��λ
	time1[8] = buffer[3] / 16 + '0';
	//�� βλ
	time1[9] = buffer[3] % 16 + '0';
	
	for (i=10; i<=15; i++)
	{
		time1[i] = ' ';
	}
	///////////////////
	////����
	///////////////////
	
	//Сʱ ��λ
	time2[0] = buffer[2] / 16 + '0';
	//Сʱ βλ
	time2[1] = buffer[2] % 16 + '0';
	
	time2[2] = ':';
	//���� ��λ
	time2[3] = buffer[1] / 16 + '0';
	//���� βλ
	time2[4] = buffer[1] % 16 + '0';
	
	time2[5] = ':';
	//�� ��λ
	time2[6] = buffer[0] / 16 + '0';
	//�� βλ
	time2[7] = buffer[0] % 16 + '0';
	// �ָ�
	time2[8] = ' ';
	
	if (time2[0] == '0')
	{
		time2[9] = 'A';
	}
	else if (time2[0] == '1')
	{
		if (time2[1] >= '2')
		{
			time2[9] = 'P';
		}
		else
		{
			time2[9] = 'A';
		}
	}
	else
	{
		time2[9] = 'P';
	}
	

	time2[10] = 'M';
	for (i=11; i<=15; i++)
	{
		time2[i] = ' ';
	}
	
}


void dataChange(void)
{
	uchar n, key, flag = 0;
//	uchar buffer[7] = {0x00, 0x00, 0x15, 0x06, 0x06, 0x00, 0x22};
//                      0��   1��   2ʱ   3��   4��    5��   6��	
	//time1���� �� �� ��ʾ��ʽ
	//time2: ʱ �� �� ��ʾ��ʽ
	//��ȡ7���ֽڵ�ʱ���źţ�����ʱ��������
	Ds1302ReadTime();
	for (n=0; n<7; n++)
	{
		buffer[n] = TIME[n];
	}
	Lcm_Init();
	while(1)
	{
		if (flag == 0)
		{
			Display_String(1, "�޸�--��        ");
		}
		else if(flag == 1)
		{
			Display_String(1, "�޸�--��        ");
		}
		else if(flag == 2)
		{
			Display_String(1, "�޸�--��        ");
		}
		else if(flag == 3)
		{
			Display_String(1, "�޸�--ʱ        ");
		}
		else if(flag == 4)
		{
			Display_String(1, "�޸�--��        ");
		}
		else if(flag == 5)
		{
			Display_String(1, "�޸�--��        ");
		}
		
		dataProcess_new();
		Display_String(2, time1);
		Display_String(3, time2);
		Display_String(4, "1Flag2Add3Bub4RE");
		
		key = key_scan();
		// �޸�flag
		if (key == 1){
			flag ++;
			if (flag == 6)flag = 0;
		}
		else if (key == 2){
			uchar date, n;
			if (flag == 0)
			{
				n = 6;
			}
			else if (flag == 1)
			{
				n = 4;
			}
			else if (flag == 2)
			{
				n = 3;
			}
			else if (flag == 3)
			{
				n = 2;
			}
			else if (flag == 4)
			{
				n = 1;
			}
			else if (flag == 5)
			{
				n = 0;
			}
			date = buffer[n] + 1;
			buffer[n] = date;
		}
		else if (key == 3){
			uchar date, n;
			if (flag == 0)
			{
				n = 6;
			}
			else if (flag == 1)
			{
				n = 4;
			}
			else if (flag == 2)
			{
				n = 3;
			}
			else if (flag == 3)
			{
				n = 2;
			}
			else if (flag == 4)
			{
				n = 1;
			}
			else if (flag == 5)
			{
				n = 0;
			}
			date = buffer[n] - 1;
			buffer[n] = date;
		}
		else if (key == 4){break;}
	}

	Ds1302Write(0x8E,0X00);//��ֹд���������ǹر�д��������
	for (n=0; n<7; n++)//д��7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		Ds1302Write(WRITE_RTC_ADDR[n], buffer[n]);
	}
	Ds1302Write(0x8E,0x80);//��д��������
}

void setClock(void)
{
	uchar n, key, flag = 0, i;
//	uchar buffer[7] = {0x00, 0x00, 0x15, 0x06, 0x06, 0x00, 0x22};
//                      0��   1��   2ʱ   3��   4��    5��   6��	
	//time1���� �� �� ��ʾ��ʽ
	//time2: ʱ �� �� ��ʾ��ʽ
	//��ȡ7���ֽڵ�ʱ���źţ�����ʱ��������
	Ds1302ReadTime();
	for (n=0; n<7; n++)
	{
		buffer[n] = TIME[n];
	}
	Lcm_Init();
	while(1)
	{
		if (flag == 0)
		{
			Display_String(1, "�����޸�--��    ");
		}
		else if(flag == 1)
		{
			Display_String(1, "�����޸�--��    ");
		}
		else if(flag == 2)
		{
			Display_String(1, "�����޸�--��    ");
		}
		else if(flag == 3)
		{
			Display_String(1, "�����޸�--ʱ    ");
		}
		else if(flag == 4)
		{
			Display_String(1, "�����޸�--��    ");
		}
		else if(flag == 5)
		{
			Display_String(1, "�����޸�--��    ");
		}
		
		dataProcess_new();
		Display_String(2, time1);
		Display_String(3, time2);
		
		key = key_scan();
		// �޸�flag
		if (key == 1){
			flag ++;
			if (flag == 6)flag = 0;
		}
		else if (key == 2){
			uchar date, n;
			if (flag == 0)
			{
				n = 6;
			}
			else if (flag == 1)
			{
				n = 4;
			}
			else if (flag == 2)
			{
				n = 3;
			}
			else if (flag == 3)
			{
				n = 2;
			}
			else if (flag == 4)
			{
				n = 1;
			}
			else if (flag == 5)
			{
				n = 0;
			}
			date = buffer[n] + 1;
			buffer[n] = date;
		}
		else if (key == 3){
			uchar date, n;
			if (flag == 0)
			{
				n = 6;
			}
			else if (flag == 1)
			{
				n = 4;
			}
			else if (flag == 2)
			{
				n = 3;
			}
			else if (flag == 3)
			{
				n = 2;
			}
			else if (flag == 4)
			{
				n = 1;
			}
			else if (flag == 5)
			{
				n = 0;
			}
			date = buffer[n] - 1;
			buffer[n] = date;
		}
		else if (key == 4){break;}
	}
	
	for (i = 0; i < 8; i++)
	{
		clocktime[i] = buffer[i];
	}
}

uchar alarmDetect(void)
{
	uchar i, Alarm = 0;
	Ds1302ReadTime();
	for (i = 0; i < 3; i++)
	{
		if (clocktime[i] == TIME[i])Alarm++;
	}
	if(Alarm == 3)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void blue2time(uchar flag, uchar pos)
{
		uchar i, n, a;
	  Ds1302ReadTime();
		for(i=0;i<8;i++)
		{
			buffer[i] = TIME[i];
		}
		a = buffer[pos] + 2 * flag - 1;

		buffer[pos] = a;
		Ds1302Write(0x8E,0X00);//��ֹд���������ǹر�д��������
		for (n=0; n<7; n++)//д��7���ֽڵ�ʱ���źţ�����ʱ��������
		{
			Ds1302Write(WRITE_RTC_ADDR[n], buffer[n]);
		}
		Ds1302Write(0x8E,0x80);//��д��������
}
void blue2clocktime(uchar flag, uchar pos)
{
	uchar buffer;
	buffer = clocktime[pos] + 2 * flag - 1;
	clocktime[pos] = buffer;
}