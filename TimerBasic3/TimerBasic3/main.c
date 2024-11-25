/*
 * TimerBasic3.c
 *
 * Created: 2024-11-25 오후 1:00:56
 * Author : tshoon
 */ 

#include <avr/io.h>
#include "board.h"
#include "fnd.h"
#include "signal_table.h"

uint8_t i= 0;

ISR(TIMER5_COMPA_vect){
	OCR2A = signal_table[i++];
}
void ioport_init(void){
	
}
void timer_init(void){
	TCCR2A = _BV(COM2A1) | _BV(WGM21)| _BV(WGM20) ; // Fast PWM mode, OC2A output
	TCCR2B = _BV(CS20); // prescaler 1
	OCR2A = 127; // Duty cycle 50% : (1+TOP)/2 -1 

	TCCR3A = _BV(COM3A1) |_BV(WGM31); // Phase collect PWM mode
	TCCR3B = _BV(WGM33) | _BV(CS31); // prescaler 8, 
	ICR3 = 1000; // F_CPU/(2*8*freq), freq = 1000  
	OCR3A = 500; // Duty cycle 50% : TOP/2 
	
	TCCR5B = _BV(WGM52) | _BV(CS51); // CTC mode, prescaler 8
	OCR5A = 1952;  // F_CPU/(8*256*4) -1;
}
void interrupt_init(void){
	sei();
}
void set_timer3_dutycycle(uint8_t dutycycle){
	OCR3A = 40*dutycycle; // ((ICR3+1)/100)*dutycycle
}
int main(void)
{
	ioport_init();
	timer_init();
	interrupt_init();
	fnd_init();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

