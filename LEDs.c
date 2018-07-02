//實驗二 多個外部中斷源控制
#include "reg51.h"
#define SIZE 8
/***************************************************/
/* a period = (65535 - 50000) = 3CAF (0.05 s/pulse) */
/* 0.05 x 20 = 1 s/pulse */
/***************************************************/
#define _TH0_ 0x3c
#define _TL0_ 0xaf
#define COUNTER 20
void delay(int t);
void show(int method);
code char light[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
char counter;
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
int x;
if (method ==0 || method == 2)
{
for (x=0;x<SIZE;x++)
{
P1=light[x];
delay(10000);
}
}
if (method ==1 || method == 2)
{
for (x=SIZE-1;x>=0;x--)
{
P1=light[x];
delay(10000);
}
}
}
void delay(int t)
{
int x;
for (x=0;x<t;x++);
}