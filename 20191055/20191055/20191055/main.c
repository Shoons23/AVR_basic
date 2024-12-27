/*
 * 20191055.c
 *
 * Created: 2024-12-19 오후 7:00:21
 * Author : owner
 */ 

#include "board.h"
#include "fnd.h"
#include "uart.h"
#include "sound.h"
#include "music_data.h"

#define CR		13
#define LF		10


// GLOBAL VARIABLE
uint16_t fnd_num = 123;
uint8_t led_pattern = 0xAA;
uint8_t note_idx;
uint16_t note_size = sizeof(m_notes)/sizeof(uint16_t);

volatile uint8_t speaker_mode = 0;
volatile uint8_t led_mode = 1;
volatile uint8_t fnd_mode = 1;

volatile uint8_t counter = 0;

ISR(USART0_RX_vect){
	// problem 3
	if(UDR0 == 'm' || UDR0 == 'M'){
		speaker_mode = !speaker_mode;
	}
	// problem 2 
	if(UDR0 >= 'A' && UDR0 <= 'Z'){
		UDR0 = UDR0;
	}
    if(UDR0 == CR){
	    UDR0 = UDR0;    // CR 
	    UDR0 = LF;
    }
}

ISR(INT3_vect){
	fnd_mode = !fnd_mode;
}

ISR(INT7_vect){
	led_mode = !led_mode;
}

ISR(TIMER5_COMPA_vect) {
	counter++;
	if(!(led_mode)){
		led_pattern ^= 0xFF;
	}
	if (counter % 4 == 0) {
		if(!(fnd_mode))	{
			fnd_num++;
		}	

	}
}

// ----------------------------------------------- myfunction ---------------------------------------------------
void my_delay_ms(uint16_t ms){
	for(uint16_t i=0; i<ms; i++) {
		_delay_ms(1);
	}
}

void sound_Q(void){
	if(m_notes[note_idx] == 0){
		sound_mute();
		my_delay_ms(m_duration[note_idx]*music_tempo);
	}
	else{
		sound_set_frequency(m_notes[note_idx % note_size]);
		my_delay_ms(m_duration[note_idx%note_size]*music_tempo);
		note_idx++;
	}
}

// ----------------------------------------------- init ---------------------------------------------------

void ioport_init(void){
	DDRB = _BV(LED_COLOR);
	DDRC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	DDRE = _BV(SOUND_OUT);
	
	PORTE = _BV(SW2);
	PORTD = _BV(SW3);
}
void interrupt_init(void){
	EICRA = _BV(ISC31); 
	EICRB = _BV(ISC71); 
	EIMSK = _BV(INT7) | _BV(INT3); 
	sei();
}

void timer_init(void) {
	TCCR3A = _BV(COM3A0);
	TCCR3B = _BV(WGM32);
	
	// TIMER 5: CTC mode(4), TOP = OCRnA, prescaler = 256
	TCCR5B |= _BV(WGM52) | _BV(CS52);      // CS52:0 = 100 
	TCCR5A |= _BV(COM5A0);
	
	OCR5A = F_CPU/(256*2) - 1;             // 0.5s period
	TIMSK5 |= _BV(OCIE5A);
}


int main(void)
{
	ioport_init();
	fnd_init();
	uart_init();
	interrupt_init();
	timer_init();
	
	/* Replace with your application code */
	fdevopen(uart_putch, uart_getch);
	while (1)
	{
		led_write(led_pattern);
		fnd_write_numbers(fnd_num);
		if(speaker_mode){
			sound_Q();
		}
		else{
			sound_mute();
		}
	}
}  
