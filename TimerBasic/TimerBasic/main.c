/*
 * TimerBasic.c
 *
 * Created: 2024-11-16 오전 1:37:12
 * Author : tshoon
 */ 

#include <avr/io.h>
#include "board.h"
#include "fnd.h"

ISR(TIMER5_COMPA_vect){
	PORTB ^= _BV(PB5);
}

void timer_init(void){
	TCCR3A |= _BV(COM3A0) | _BV(COM3B0); // Comapare Output Mode setting: toggle 
	TCCR3B |= _BV(WGM32) |_BV(CS31); // 16 bit timer 3, CTC mode , 250 clk, prescaler 8
	TIFR3 = _BV(OCF3A); // Compare Match flag set
	
	OCR3A = 249;
	OCR3B = 124;
	
	TCCR5B |= _BV(WGM52)| _BV(CS51) | _BV(CS50);// 16 bit timer 5, CTC mode, prescaler 64
	TIMSK5 |= _BV(TOIE5); // overflow interrupt enable
	
	// 100 = (F_CPU/prescaler-n)/1+OCR5A_value
	OCR5A = F_CPU/(64*100) - 1;
}

void ioport_init(void){
	DDRB |= _BV(PB5);
	DDRE |= _BV(SOUND_OUT)|_BV(PE4);
}

void interrupt_init(void){
	sei();
}



int main()
{
	
	ioport_init();
	interrupt_init();
	timer_init();
	
	while(1){
	
	}
}






// 5. 
//ISR(TIMER5_OVF_vect){
	//PORTB ^= _BV(PB5);
	//TCNT5 = -2500;
//}

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
//int main()
//{
	//timer_init();
	//
	//DDRB = _BV(PB5);
	//TCNT5 = -2500;
	//
	//while(1){
		//if(TIFR5&&_BV(TOV5)){
			//PORTB ^= _BV(TOV5);
			//TIFR5 = _BV(TOV5);
			//TCNT5 = 63356;
		//}
	//}
//}
