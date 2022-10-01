/*

header.h

*/
#ifndef __header__
#define	__header__
///////////////////////////////DEFINE/////////////////
#define TRUE 1
#define FALSE 0
#define lcd_clear()	lcd_cmd(0x01)
#define cursor_on 0x0E
#define cursor_off 0x0C
#define blink_on	0x0F
#define	go_home 0x02
#define	flfc	0x80
#define slfc	0xC0

#define loopback TRUE
///////////////////////////////LCD Functions/////////////
void delay_ms(unsigned int);
void lcd_data(unsigned char);
void lcd_cmd(unsigned char);
void lcd_init(void);
void lcd_string(const char *);
void lcd_welcome(const char *);
void lcd_scroll(const char *);
void lcd_circular(const char *);
void lcd_circular2(const char *,const char *);
bit IO_read(const char,const char);
void lcd_int(long int);
void lcd_float(float);

///////////////////////UART Functions////////////////////
void uart_init(unsigned int);
void uart_tx(unsigned char);
unsigned char uart_rx(void);
void uart_tx_string(const char *);
void uart_rx_string(char *,unsigned int);


//////////////extra/////////////////////////////////////
void eval(char ,char *, int *);
#endif