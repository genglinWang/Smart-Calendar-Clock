#ifndef __DS1302_H_
#define __DS1302_H_

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

//---����ds1302ʹ�õ�IO��---//

//---����ȫ�ֺ���---//
void Ds1302Write(uchar addr, uchar dat);
uchar Ds1302Read(uchar addr);
void Ds1302Init();
void Ds1302ReadTime();
void dataProcess();
void dataChange(void);
void setClock(void);
uchar alarmDetect(void);
void blue2time(uchar flag, uchar pos);
void blue2clocktime(uchar flag, uchar pos);
//---����ȫ�ֱ���--//
extern uchar TIME[7];	//����ȫ�ֱ���
extern uchar displayData[16];
extern uchar displayData2[16];
extern uchar buffer[7];
extern uchar clocktime[7];

#endif