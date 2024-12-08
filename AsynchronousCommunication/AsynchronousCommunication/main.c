/*
 * AsynchronousCommunication.c
 *
 * Created: 2024-12-02 오전 10:20:04
 * Author : tshoon
 */ 

#include <avr/io.h>
#include "board.h"
#include "uart.h"
#include <stdio.h>
#include "fnd.h"

#define CR 13
#define LF 10

ISR(USART0_RX_vect){
	UDR0 = UDR0;
	fnd_write_numbers(999);
}


int main(void)
{
	uint8_t ch;
	
	fnd_init();
	uart_init();
	sei();
	
	fdevopen(uart_putch, uart_getch);

	while (1) 
    {	
		//scanf("%c", &ch);  
		//if(ch == 13){
			//uart_putch(CR);
			//uart_putch(LF);
			//uart_puts("UCSR0B: 0x");
			//printf("%X", UCSR0B);
			//uart_putch(CR);
			//uart_putch(LF);
		//}
		//else
		//uart_putch(ch);
		
    }
}

