#ifndef __BLUETOOTH_H_
#define __BLUETOOTH_H_

//---����ͷ�ļ�---//
#include<reg52.h>
#include<intrins.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif


//---����ȫ�ֺ���---//
void Uart_Init_blue(void);
void PostChar(uchar character);
//---����ȫ�ֱ���--//
extern uchar weather;

#endif