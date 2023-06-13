#include <reg51.h>
#include <string.h>
#include <stdio.h>

/*
Uart_Init:串口初始化程序
返回:无
参数:无
*/
void Uart_Init(void)
{
	TL1=0xfa;	//在11.0592MHz晶振下，设置波特率9600，工作方式2
	TH1=0xfa;
	TMOD=0x20;
	SCON=0x50;	//串口工作方式1，允许接收
	PCON=0x80;
	EA=0;
	REN=1;
	TI=0;		//发送中断标志位
	RI=0;		//接收中断标志位
	TR1=1;		//定时器1用作波特率发生器
}

/*
Putchar:串口发送1个字符底层程序，配置好后可以用标准C函数printf来发数据
返回:是否执行成功
参数:c 发送的字符
*/
char putchar(char c)
{
	TI=0;
	SBUF=c;
	while(TI==0);
	return 1;
}
/*
Delay_ms:延迟1ms函数（非精确）
返回:无
参数:x 多少个1ms
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
main:主函数 串口循环发送"大家好"
返回:无
参数:无
*/
void main(void)
{
	Uart_Init();//串口初始化
	while(1)
	{
		printf("大家好");		//串口输出"大家好"
		Delay_ms(5000);		//延迟5秒
	}
}


