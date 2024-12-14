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
#include "led_pattern.h"

static uint8_t signal_idx= 0;
static uint8_t pattern_idx= 0;
volatile uint8_t duty_cycle= 50;

ISR(INT3_vect){
	if(duty_cycle > 0)
	duty_cycle -= 10;
}
ISR(INT7_vect){
	if(duty_cycle < 100)
	duty_cycle += 10;
}

ISR(TIMER5_COMPA_vect){
	OCR2A = signal_table[signal_idx++];
}
void ioport_init(){
	DDRB |= _BV(PB4); // OC2A output
	DDRE |= _BV(PE3); // OC3A output
	
	PORTD = _BV(SW3); // pull-up resistor enable
	PORTE = _BV(SW2); // pull-up resistor enable
}
void timer_init(void){
	TCCR2A = _BV(COM2A1) | _BV(WGM21)| _BV(WGM20) ; // Fast PWM mode, OC2A output
	TCCR2B = _BV(CS20); // prescaler 1
	OCR2A = 127; // Duty cycle 50% : (1+TOP)/2 -1 

	TCCR3A = _BV(COM3A1) |_BV(WGM31); // Phase correct PWM mode
	TCCR3B = _BV(WGM33) | _BV(CS31); // prescaler 8 
	ICR3 = 1000; // F_CPU/(2*8*freq), freq = 1000  
	OCR3A = 500; // Duty cycle 50% : TOP/2 
	
	TCCR5B = _BV(WGM52) | _BV(CS51); // CTC mode, prescaler 8
	OCR5A = 1952;  // F_CPU/(8*256*4) -1;
}
void interrupt_init(void){
	EICRA = _BV(ISC31); // Falling edge trigger
	EICRB = _BV(ISC71); 
	EIMSK = _BV(INT7) | _BV(INT3); // External interrupt enable
	
	TIMSK5 = _BV(OCIE5A);
	
	sei();
}
void set_timer3_dutycycle(uint8_t dutycycle){
	OCR3A = 10*dutycycle; // (TOP/100)*dutycycle 
}
int main(void)
{
	ioport_init();
	timer_init();
	interrupt_init();
	fnd_init();
	
    while (1) 
    {
		led_write(led_pattern[pattern_idx++%8]);
		_delay_ms(250);
		set_timer3_dutycycle(duty_cycle);	
    }
}

