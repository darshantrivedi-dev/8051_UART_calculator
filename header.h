/*

header.h

*/
#ifndef __header__
#define	__header__
///////////////////////////////DEFINE/////////////////
#define TRUE 1
#define FALSE 0

#define loopback TRUE

///////////////////////UART Functions////////////////////
void uart_init(unsigned int);
void uart_tx(unsigned char);
unsigned char uart_rx(void);
void uart_tx_string(const char *);
void uart_rx_string(char *,unsigned int);


//////////////extra/////////////////////////////////////
void eval(char ,char *, int *);
#endif
