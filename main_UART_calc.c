/*		main_UART_calc.c
 *		
 *		uC:	AT89C51
 *		UART Baud: 9600 bps
 *		MAX Operand Supported 11 (Max 10 Operation on Single Expressions)
 *		-32768>=ANS OR OPERAND<=32767	else RIP.
 */
#include "header.h"

#define max_oprand	11
#define max_buffer	max_oprand*6

void main()
{
	int oprand[max_oprand+1];
	unsigned char oprator[max_oprand],i,j,k;
	unsigned char buffer[max_buffer];
	
	uart_init(9600);
	
	uart_tx_string("Max 10 Operation (11 Operands) on Single Expressions supported,\r\n-32768>=ANS OR OPERAND<=32767 else RIP.\r\n\r\n");
	while(1)
	{	
		uart_tx_string("Enter Expression:");
		uart_rx_string(buffer,max_buffer-1);

/////////////////////////////////////EXTRACT VALS AND OPERATION//////////////////////////////////////
		for(i=0,j=0,k=0;i<max_oprand;i++)
			oprand[i]=oprator[i]=0;
		oprand[i]=0;
		
		i=0;
		while(buffer[i])
		{
			while(buffer[i]>='0' && buffer[i]<='9')
			{
				oprand[j]=oprand[j]*10+buffer[i]-48;
				i++;
			}
			j++;
			if(buffer[i])
				oprator[k++]=buffer[i++];
		}
	
////////////////////////////////////////EVAL + UPDATE ARRAY///////////////////////////////////////////////////		
		i=0;	
		while(oprator[i])
		{
			if(oprator[i]=='%'){
				oprand[i]=oprand[i]%oprand[i+1];
				eval(i,oprator,oprand);
				continue;
			}
			else if(oprator[i]=='/'){
				oprand[i]=oprand[i]/oprand[i+1];
				eval(i,oprator,oprand);
				continue;
			}
			else if(oprator[i]=='*'){
				oprand[i]=oprand[i]*oprand[i+1];
				eval(i,oprator,oprand);
				continue;
			}
			i++;
		}
			
			i=0;
		while(oprator[i])
		{
			if(oprator[i]=='+'){
				oprand[i]=oprand[i]+oprand[i+1];
				eval(i,oprator,oprand);
			}
			else if(oprator[i]=='-'){
				oprand[i]=oprand[i]-oprand[i+1];
				eval(i,oprator,oprand);
			}
		}
		
		uart_tx_string("\r\nAnswer is:");
		if(oprand[0]<0){
			uart_tx('-');
			oprand[0]=-oprand[0];
		}
		uart_tx((oprand[0]/10000)%10+48);
		uart_tx((oprand[0]/1000)%10+48);
		uart_tx((oprand[0]/100)%10+48);
		uart_tx((oprand[0]/10)%10+48);
		uart_tx(oprand[0]%10+48);
		
		uart_tx_string("\r\n");
	}
}
void eval(char i,char *opt, int *opr)
{
	unsigned char k;
	
	for(k=i+1;opr[k];k++)
	{
		opr[k]=opr[k+1];opt[k-1]=opt[k];
	}
}