//51��Ƭ��������ʪ�ȴ�����DHT11��Ȼ����LCD1602����ʾ��ǰ����ʪ�ȼ���λ������ʪ���ڵ�һ����ʾ���¶��ڵڶ�����ʾ����Ƭ��ΪYL-9��Сϵͳ��

# include <reg51.h>
# include <intrins.h>
typedef unsigned char BYTE;
typedef unsigned int WORD;
#define uint unsigned int 
#define uchar unsigned char 
sbit io=P1^0;//dht11data�˽ӵ�Ƭ����P1^0��// 

sbit rw=P2^4;//һ������������lcd1602��ʹ�ܶ�// 

sbit rs=P2^3; 

sbit ep=P2^5; 

typedef bit BOOL;//������һ�������ͱ���������// 

uchar data_byte; 

uchar RH,RL,TH,TL; 

 

//***************��ʱ����************************************* 

 void delay(uchar ms) //��ʱģ��// 

{ 

  uchar i; 

  while(ms--)                 

        

 for(i=0;i<100;i++); 

} 


void delay1()//һ��forѭ�������Ҫ8����������ڪ�һ����������Ϊ1us������Ϊ12MHz����Ҳ����˵��������ʱ8us�ડ����ʱ�����������΢��ȷһ�㪢 

{ 

  uchar i; 

  for(i=0;i<1;i++); 

} 

  

//***************************************************************  

//lcdģ��// 

BOOL lcd_bz()//����lcdæµ״̬������ֵΪ��������ֵ�����٪�'1'.'0'��  

{ 

 BOOL result;
  rs=0;           // ��æ�ź�
  rw=1;
  ep=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  result = (BOOL)(P0&0x80);
  ep=0;
  result ;

}     

void write_cmd(uchar cmd)//дָ��// 

{ 

  while (lcd_bz());
  rs=0;
  rw=0;
  ep=0;
  _nop_();
  _nop_();
  P0=cmd ;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  ep=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  ep=0;

} 

 

void write_addr(uchar addr)//д��ַ// 

{ 

  write_cmd(addr|0x80);//LCD��һ�е��׵�ַΪ0x80���ڶ��е��׵�ַΪ0x80+0x40=0xc0 

} 

 

void write_byte(uchar dat) //д�ֽ�// 

{ 

   while (lcd_bz());
  rs=1;
  rw=0;
  ep=0;
  _nop_();
  _nop_();
  P0=dat ;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  ep=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  ep=0;

} 

 

void lcd_init() //lcd��ʼ��// 

{ 

  write_cmd(0x38);//����LCD������ʾ��һ��������5*7�����ʾ,������8���ߴ��� 

  delay(1); 

  write_cmd(0x0c);//�����Ļ��ʾ 

  delay(1); 

  write_cmd(0x06);//�趨���뷽ʽ����������λ 

  delay(1); 

  write_cmd(0x01);//��������ʾ���ع�ꪡ����˸ 

  delay(1); 

} 

 

void display(uchar addr,uchar q)//��ĳһ��ַ����ʾ���ݪ�adder��ʾ���ǵ�ַƫ������q��ʾ��ʾ���ַ�������// 

{ 

  delay(10);   write_addr(addr); 

  write_byte(q); 

  delay(1);//�޸Ĵ�ʱ�䪣���Ըı�LCD����ֵ��������� 

} 

 

//**************************dht11����ĳ��*************************************// 

void start()//��ʼ�ź� 

{ 

  io=1; 

  delay1(); 

  io=0; 

  delay(25);// �������������ͱ������18ms����֤DHT11�ܼ�⵽��ʼ�ź� 

  io=1;    //���Ϳ�ʼ�źŽ��������ߵ�ƽ��ʱ20-40us 

  delay1();//����������ʱ�������Ϊ24us������Ҫ�� 

  delay1(); 

  delay1(); 

} 

 

uchar receive_byte()//����һ���ֽ�// 

{ 

  uchar i,temp; 

  for(i=0;i<8;i++)//����8bit������ 

  { 

 	while(!io);//�ȴ�50us�ĵ͵�ƽ��ʼ�źŽ��� 

 	delay1();//��ʼ�źŽ���֮����ʱ26us-28us������������ʱ������ 

	 delay1(); 

 	delay1(); 

 	temp=0;//ʱ��Ϊ26us-28us����ʾ���յ�Ϊ����'0' 

 	if(io==1) 

	 temp=1; //���26us-28us֮�󪣻�Ϊ�ߵ�ƽ�����ʾ���յ�����Ϊ'1' 

    while(io);//�ȴ������źŸߵ�ƽ��'0'Ϊ26us-28us��'1'Ϊ70us�� 

 	data_byte<<=1;//���յ�����Ϊ��λ��ǰ�����ƪ� 

	 data_byte|=temp; 

  } 

  return data_byte; 

} 

    

void receive()//��������// 

{ 

  uchar T_H,T_L,R_H,R_L,check,num_check,i; 

  start();//��ʼ�ź�// 

  io=1;   //������Ϊ���몣�жϴӻ���DHT11����Ӧ�ź� 

  if(!io)//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź�// 

  {  
	while(!io);//�жϴӻ����� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����// 

	while(io);//�жϴӻ����� 80us �ĸߵ�ƽ�Ƿ������������������������ݽ���״̬ 

	R_H=receive_byte();//ʪ�ȸ�λ 

 	R_L=receive_byte();//ʪ�ȵ�λ 

	T_H=receive_byte();//�¶ȸ�λ 

	T_L=receive_byte();//�¶ȵ�λ 

	check=receive_byte();//У��λ 

	io=0; //�����һbit���ݽ���Ϻ󪣴ӻ����͵�ƽ50us// 

	for(i=0;i<7;i++)//���50us����ʱ 

	delay1(); 

	io=1;//�����������������ߪ��������״̬ 

	num_check=R_H+R_L+T_H+T_L; 

	if(num_check==check)//�ж϶������ĸ�����֮���Ƿ���У��λ��ͬ 

 	{ 

   RH=R_H; 

   RL=R_L; 

   TH=T_H; 

   TL=T_L; 

   check=num_check; 

 	} 

  } 

} 

//*****************************************************************************

 

void main()//������ģ��// 

{ 

  lcd_init();//��ʼ��LCD 

  while(1) 

  { 

    receive();//�������� 

 display(0x00,'R');//LCD�ĵ�һ����ʾ 

 display(0x01,':'); 

 display(0x02,RH/10+0x30); //0x30��ʾ�����ֿ��LCD1602��0x30��λ�÷�������0��RH/10+0x30����ʾʪ�ȵ�ʮλ�������ֿ�RH/10+0x30��λ�ô����Ū� 

 display(0x03,RH%10+0x30); 

 display(0X04,'%'); 

 display(0x40,'T');//LCD�ĵڶ�����ʾ 

 display(0x41,':'); 

 display(0x42,TH/10+0x30); 

 display(0x43,TH%10+0x30); 

 display(0x44,0xdf);//�����������¶ȵ�λ�Ĵ��� 

 display(0x45,0x43); 

  } 
} 






