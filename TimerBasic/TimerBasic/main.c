/*
 * TimerBasic.c
 *
 * Created: 2024-11-16 오전 1:37:12
 * Author : tshoon
 */ 

#include <avr/io.h>
#include "board.h"
#include "fnd.h"

void ioport_init(void)
{
	DDRB |= _BV(LED_COLOR);
	DDRC |= _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTE |= _BV(SW2);
	PORTD |= _BV(SW3) | _BV(SW4);
}

void interrupt_init(void){
	PCMSK0 |= _BV(PCINT5) | _BV(PCINT6); // PCINT0's pins masking to enable
	PCICR |= _BV(PCIE0); // PCINT0 control register enable
	sei();
}

void timer_init(void){
	TCCR3B |= _BV(WGM32) |_BV(CS31); // 16 bit timer 3, CTC, 250 clk, prescaler 8
	OCR3A = 249;
	TCCR5B |= _BV(CS51) | _BV(CS50);// 16 bit timer 5, normal, prescaler 64
}

// 5. 
ISR(TIMER5_OVF_vect){
	PORTB ^= _BV(PB5);
	TCNT5 = -2500;
}

//3. 
//int main()
//{
	//timer_init();
	//DDRE = _BV(PE3);
	//
	//while(1){
		//if(TIFR3&_BV(OCF3A)){
			//PORTE ^= _BV(PE3);
			//TIFR3 = _BV(OCF3A); // Timer3 Interrupt Flag clear
		//}
	//}
//}

// 4.
int main()
{
	timer_init();
	
	DDRB = _BV(PB5);
	TCNT5 = -2499;
	
	while(1){
		if(TIFR5&&_BV(TOV5)){
			PORTB ^= _BV(TOV5);
			TIFR5 = _BV(TOV5);
			TCNT5 = 63356;
		}
	}
}
