/*
 * uart.c
 *
 * Created: 2024-12-02 오후 3:35:06
 *  Author: tshoon
 */ 

#include "board.h"

void uart_init(void){
	#define BAUDRATE 115200L
	
	UBRR0 = F_CPU/(8*BAUDRATE) -1; // error : 2.1%
	UCSR0A = _BV(U2X0); // Double Speed Mode
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);//  Rx, Tx enable
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8bit character size
	
}
int8_t uart_getch(void)
{
	while(!(UCSR0A & _BV(RXC0))); // if UDR0 is fulled, clear
	return UDR0;
}
void uart_putch(int8_t ch){
	while(!(UCSR0A & _BV(UDRE0))); // UDRE0 
	UDR0 = ch;
}
void uart_puts(int8_t *str){
	while(*str != '\0')
	uart_putch(*str++);
}

void num2ascii(int8_t ch){
	int8_t tmp;
	
	tmp = (ch>>4) & 0x0f;
	if(tmp >= 0 && tmp <= 9)
		uart_putch(tmp + '0');
	else
		uart_putch(tmp + 'A' - 10);
	
	tmp = ch & 0x0f;
	if(tmp >= 0 && tmp <= 9)
		uart_putch(tmp + '0');
	else
		uart_putch(tmp + 'A' - 10);
}
