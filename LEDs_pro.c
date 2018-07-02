//實驗二 多個外部中斷源控制
#include "reg51.h"
#define SIZE 4
/***************************************************/
/* a period = (65535 - 50000) = 3CAF (0.05 s/pulse) */
/* 0.05 x 20 = 1 s/pulse */
/***************************************************/
#define _TH0_ 0x3c
#define _TL0_ 0xaf
#define COUNTER 20
void delay(int t);
void show(int method);
code char light[] = {0xfc,0xf3,0xcf,0x3f};
char counter;
int count ;

void main()
{
TCON=0x00;
TMOD=0x01;
IP=0x01;
IE=0x83;
TL0 = _TL0_;
TH0 = _TH0_;
TR0 = 1;
P1 = 0xff;
counter = 1;
count = 0 ;
while(1){;}
}

void tmiintrt(void) interrupt 1
{
TL0 = _TL0_;
TH0 = _TH0_;
counter++;
if (counter == COUNTER)
{
if (P1 == 0xff)
P1 = 0x00;
else
P1 = 0xff;
counter = 1;
}
}

void intx(void) interrupt 0
{
if(P3==0xfa)
show(0);
else if (P3 == 0xf9)
show(1);
else
show(2);
}

void show(int method)
{
int x,z;
int y;
int a,c;
int b;
if (method ==0 || method == 2)
{
for (x=0;x<SIZE;x++)
{
P1=light[x];
delay(20000);
	if(P3 == 0xfa || P3 == 0xf9)
	{

		while(1)
		{
					P1 = light[x];
					delay(20000);
			if(P3 == 0xfa || P3 == 0xf9)
			{
				if(P3 == 0xfa)
					break ;
				else if (P3 == 0xf9)
				{
					for(y=x;y>=0;y--)
						{
							P1=light[y];
							delay(20000);
						}
					return ;
				}
			}		
		}
	}

}
for (z=0;z<SIZE;z++)
{
P1=light[z];
delay(20000);
}

}
if (method ==1 || method == 2)
{
for (a=SIZE-1;a>=0;a--)
{
P1=light[a];
delay(20000);
	if(P3 == 0xfa || P3 == 0xf9)
	{

		while(1)
		{
					P1 = light[a];
					delay(20000);
			if(P3 == 0xfa || P3 == 0xf9)
			{
				if(P3 == 0xf9)
					break ;
				else if (P3 == 0xfa)
				{
					for(b=a;b<SIZE;b++)
						{
							P1=light[b];
							delay(20000);
						}
					return ;
				}
			}		
		}
	}
}
for (c=SIZE-1;c>=0;c--)
{
P1=light[c];
delay(20000);
}
}
}

void delay(int t)
{
int x;
for (x=0;x<t;x++);

}