#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit Data = P1 ^ 0;

void DHT11_delay_us(uchar n)
{
    while (--n)
        ;
}

void DHT11_delay_ms(uint z)
{
    uint i, j;
    for (i = z; i > 0; i--)
        for (j = 110; j > 0; j--)
            ;
}

void Delay30us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 80;
	while (--i);
}

void DHT11_start()
{
    Data	= 1;
    DHT11_delay_us(2);
	
    Data = 0;
    DHT11_delay_ms(20);

    Data = 1;
    DHT11_delay_us(30);

}

uchar DHT11_rec_byte()
{
    uchar i, dat = 0;
    for (i = 0; i < 8; i++)
    {
        while (!Data)
            ;
        DHT11_delay_us(8);
        dat <<= 1;
        if (Data == 1)
            dat += 1;
        while (Data)
            ;
    }
    return dat;
}

// dht11不稳定，容易乱码
// 接收dht11发来的数据并格式化为lcd12864可以显示的16位字符串格式
uchar* DHT11_receive()
{
    uchar R_H, R_L, T_H, T_L, RH, RL, TH, TL, revise, rec_dat[16],i;
    DHT11_start();
    if (Data == 0)
    {
        while (Data == 0)
            ;
        DHT11_delay_us(50);
        R_H = DHT11_rec_byte();
        R_L = DHT11_rec_byte();
        T_H = DHT11_rec_byte();
        T_L = DHT11_rec_byte();
        revise = DHT11_rec_byte();
        DHT11_delay_us(25);

        if ((R_H + R_L + T_H + T_L) == revise)
        {
            RH = R_H;
            RL = R_L;
            TH = T_H;
            TL = T_L;
        }

        rec_dat[0] = '0' + (RH / 10);
        rec_dat[1] = '0' + (RL % 10);
        rec_dat[2] = 'R';
        rec_dat[3] = 'H';
        rec_dat[4] = ' ';
        rec_dat[5] = '0' + (TH / 10);
        rec_dat[6] = '0' + (TL % 10);
        rec_dat[7] = 'C';
				
				for (i=8 ; i <= 15; i++)
				{
						rec_dat[i] = ' ';
				}
    }
		return rec_dat;
}

