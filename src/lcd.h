#ifndef __LCD_H_
#define __LCD_H_

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
void Display_String(uchar line, uchar *string);
void Lcm_Init(void);
void Wr_Command(uchar wrcommand, busyc);
void Wr_Data(uchar wrdata);
void RDbf(void);
void Delay5Ms(void);
void Switch_bit(uchar InChar);
//---����ȫ�ֱ���--//

#endif