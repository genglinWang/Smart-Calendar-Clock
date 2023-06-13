//51单片机控制温湿度传感器DHT11然后在LCD1602上显示当前的温湿度及单位其中湿度在第一行显示温度在第二行显示。单片机为YL-9最小系统。

# include <reg51.h>
# include <intrins.h>
typedef unsigned char BYTE;
typedef unsigned int WORD;
#define uint unsigned int 
#define uchar unsigned char 
sbit io=P1^0;//dht11data端接单片机的P1^0口// 

sbit rw=P2^4;//一下三行是设置lcd1602的使能端// 

sbit rs=P2^3; 

sbit ep=P2^5; 

typedef bit BOOL;//此声明一个布尔型变量即真或假// 

uchar data_byte; 

uchar RH,RL,TH,TL; 

 

//***************延时函数************************************* 

 void delay(uchar ms) //延时模块// 

{ 

  uchar i; 

  while(ms--)                 

        

 for(i=0;i<100;i++); 

} 


void delay1()//一个for循环大概需要8个多机器周期一个机器周期为1us晶振为12MHz也就是说本函数延时8us多此延时函数必须德稍微精确一点 

{ 

  uchar i; 

  for(i=0;i<1;i++); 

} 

  

//***************************************************************  

//lcd模块// 

BOOL lcd_bz()//测试lcd忙碌状态返回值为布尔型数值真或假'1'.'0'  

{ 

 BOOL result;
  rs=0;           // 读忙信号
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

void write_cmd(uchar cmd)//写指令// 

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

 

void write_addr(uchar addr)//写地址// 

{ 

  write_cmd(addr|0x80);//LCD第一行的首地址为0x80第二行的首地址为0x80+0x40=0xc0 

} 

 

void write_byte(uchar dat) //写字节// 

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

 

void lcd_init() //lcd初始化// 

{ 

  write_cmd(0x38);//设置LCD两行显示一个数据由5*7点阵表示,数据由8跟线传输 

  delay(1); 

  write_cmd(0x0c);//清除屏幕显示 

  delay(1); 

  write_cmd(0x06);//设定输入方式增量不移位 

  delay(1); 

  write_cmd(0x01);//开整体显示关光标不闪烁 

  delay(1); 

} 

 

void display(uchar addr,uchar q)//在某一地址上显示内容adder表示的是地址偏移量q表示显示的字符或数字// 

{ 

  delay(10);   write_addr(addr); 

  write_byte(q); 

  delay(1);//修改此时间可以改变LCD上数值跳变的数度 

} 

 

//**************************dht11测试某块*************************************// 

void start()//开始信号 

{ 

  io=1; 

  delay1(); 

  io=0; 

  delay(25);// 主机把总线拉低必须大于18ms保证DHT11能检测到起始信号 

  io=1;    //发送开始信号结束后拉高电平延时20-40us 

  delay1();//以下三个延时函数差不多为24us符合要求 

  delay1(); 

  delay1(); 

} 

 

uchar receive_byte()//接收一个字节// 

{ 

  uchar i,temp; 

  for(i=0;i<8;i++)//接收8bit的数据 

  { 

 	while(!io);//等待50us的低电平开始信号结束 

 	delay1();//开始信号结束之后延时26us-28us以下三个延时函数 

	 delay1(); 

 	delay1(); 

 	temp=0;//时间为26us-28us表示接收的为数据'0' 

 	if(io==1) 

	 temp=1; //如果26us-28us之后还为高电平则表示接收的数据为'1' 

    while(io);//等待数据信号高电平'0'为26us-28us'1'为70us 

 	data_byte<<=1;//接收的数据为高位在前右移 

	 data_byte|=temp; 

  } 

  return data_byte; 

} 

    

void receive()//接收数据// 

{ 

  uchar T_H,T_L,R_H,R_L,check,num_check,i; 

  start();//开始信号// 

  io=1;   //主机设为输入判断从机DHT11响应信号 

  if(!io)//判断从机是否有低电平响应信号// 

  {  
	while(!io);//判断从机发出 80us 的低电平响应信号是否结束// 

	while(io);//判断从机发出 80us 的高电平是否结束如结束则主机进入数据接收状态 

	R_H=receive_byte();//湿度高位 

 	R_L=receive_byte();//湿度低位 

	T_H=receive_byte();//温度高位 

	T_L=receive_byte();//温度低位 

	check=receive_byte();//校验位 

	io=0; //当最后一bit数据接完毕后从机拉低电平50us// 

	for(i=0;i<7;i++)//差不多50us的延时 

	delay1(); 

	io=1;//总线由上拉电阻拉高进入空闲状态 

	num_check=R_H+R_L+T_H+T_L; 

	if(num_check==check)//判断读到的四个数据之和是否与校验位相同 

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

 

void main()//主函数模块// 

{ 

  lcd_init();//初始化LCD 

  while(1) 

  { 

    receive();//接收数据 

 display(0x00,'R');//LCD的第一行显示 

 display(0x01,':'); 

 display(0x02,RH/10+0x30); //0x30表示带字库的LCD1602中0x30的位置放有数字0RH/10+0x30即表示湿度的十位数字在字库RH/10+0x30的位置处放着 

 display(0x03,RH%10+0x30); 

 display(0X04,'%'); 

 display(0x40,'T');//LCD的第二行显示 

 display(0x41,':'); 

 display(0x42,TH/10+0x30); 

 display(0x43,TH%10+0x30); 

 display(0x44,0xdf);//以下两个是温度单位的处理 

 display(0x45,0x43); 

  } 
} 






