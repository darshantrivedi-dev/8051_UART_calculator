/*	uart_driver.c
 *	
 *
 *
 */

#include <reg51.h>
#include "header.h"

void uart_init(unsigned int baud)
{
	TMOD|=0x20;	//Selecting Timer1 in Mode 2(8-bit Auto-reload)
	SCON=0x50;	//Selcting Universal Mode1 of UART and Receiving Enable
	PCON&=~(1<<7);	//Clearing SCON (double baud rate) Bit
	TR1=1;	//Starting UART settings
	switch(baud)
	{
		case 7200: TH1=252;break;
		case 9600:	TH1=253;break;
		case 19200:	TH1=253;PCON|=(1<<7);break;
		case 14400:	TH1=254;break;
		case 28800:	TH1=255;break;
		case 57600:	TH1=255;PCON|=(1<<7);break;
		default:	TH1=253;
	}
}
void uart_tx_string(const char *str)
{
	while(*str)
	{
		SBUF=*str;
		while(TI==0);
		TI=0;
		str++;
	}
	/*
	char i=0;
	while(str[i])
		uart_tx(str[i++]);
	*/
}
void uart_rx_string(char *str,unsigned int max_byte)
{
	int i=0;
	while(max_byte--)
	{
		while(RI==0);
		RI=0;
		if(SBUF=='\r')
			break;
		str[i++]=SBUF;
		#if loopback==TRUE
		uart_tx(SBUF);
		#endif
	}
	str[i]=0;
}
void uart_tx(unsigned char d)
{
	SBUF=d;
	while(TI==0);
	TI=0;
}

unsigned char uart_rx(void)
{
	while(RI==0);
	RI=0;
	return SBUF;
}