#ifndef __JQ8900_H_
#define __JQ8900_H_

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

//---����jq8900ʹ�õ�IO��---//


//---����ȫ�ֺ���---//
void SendData(uint addr);
void Musicselect(void);

//---����ȫ�ֱ���--//
extern uchar song;
#endif