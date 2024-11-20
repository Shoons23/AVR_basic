/*
 * TimerBasic2.c
 *
 * Created: 2024-11-19 오후 8:21:26
 * Author : tshoon
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>  
#include "fnd.h"
#include "board.h"
#include "sound.h"
#include "music_data.h"

volatile uint16_t fnd_num = 0;
volatile uint8_t mode = 0;
volatile uint8_t note_idx = 0;

ISR(INT3_vect){
	note_idx = 0; // index 0
}

ISR(INT7_vect){
	mode ^= 1;
	if(!mode) {
		fnd_num = 0;
	}
}

ISR(TIMER5_COMPA_vect){
	fnd_write_numbers(fnd_num);
	fnd_num = (fnd_num + 1) % 1000;
}

void my_delay_ms(uint16_t ms)
{
	for(uint16_t i=0; i<ms; i++) {
		_delay_ms(1);    
	}
}

void timer_init(void)
{
	TCCR3A |= _BV(COM3A0);
	TCCR3B |= _BV(WGM32); 
	
	TCCR5B |= _BV(WGM52) | _BV(CS51) | _BV(CS50);  // prescaler 64
	TIMSK5 |= _BV(OCIE5A);
	OCR5A = F_CPU/(64*10)-1; // 16bit -> max: 65536 ~~> 24999
	
}

void interrupt_init(void)
{
	EICRA |= _BV(ISC31); // falling edge triggered
	EICRB |= _BV(ISC71); // falling edge triggered
	EIMSK |= _BV(INT7) | _BV(INT3); // interrupt enable
	sei();
}

void ioport_init(void)
{
	DDRB = _BV(LED_COLOR);  
	DDRC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	DDRE = _BV(PE3);
	
	PORTE = _BV(SW2);
	PORTD = _BV(SW3);
}



int main(void){
	
	ioport_init();
	fnd_init();
	interrupt_init();
	timer_init();
	
	fnd_write_numbers(fnd_num);
	
	uint16_t note_size = sizeof(m_notes)/sizeof(uint16_t);
	
	while(1){
		if(mode){
			if(m_notes[note_idx] == 0){
				sound_mute();
				my_delay_ms(m_duration[note_idx]);
			}
			else{
				sound_set_frequency(m_notes[note_idx%note_size]);
				my_delay_ms(m_duration[note_idx%note_size]);
				note_idx++;
			}
		}
		else{
			sound_mute();
		}
	}
}



// 5. 
//int main(void){
	//uint16_t m_notes_tmp[] = {320, 480, 320, 480, 320, 480, 320, 480, 320, 480, 320, 480, 320, 480, 320, 480, 0};
	//uint16_t m_duration_tmp[] = {80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 1000};
//
	//ioport_init();
	//fnd_init();
	//interrupt_init();
	//timer_init();
	//
	//uint8_t note_idx = 0;
	//
	//while(1){
		//note_idx = note_idx & sizeof(m_notes_tmp)/sizeof(uint16_t);
		//
		//if(m_notes_tmp[note_idx] == 0){
			//sound_mute();
			//my_delay_ms(m_duration_tmp[note_idx]);
		//}
		//else{
			//sound_set_frequency(m_notes_tmp[note_idx]);
			//my_delay_ms(m_duration_tmp[note_idx]);
			//note_idx++;	
		//}
		//
	//}
//}

// 6.
//int main(void){
	//
	//ioport_init();
	//fnd_init();
	//interrupt_init();
	//timer_init();
	//
	//while(1){
		//for(; note_idx<sizeof(m_notes)/2; note_idx++){
			//if(m_notes[note_idx]==XX){
				//sound_mute();
				//my_delay_ms(m_duration[note_idx]*music_tempo);
			//}
			//else{
				//sound_set_frequency(m_notes[note_idx]);
				//my_delay_ms(m_duration[note_idx]*music_tempo);
			//}
		//}
	//}
//}

/*int main(void)
{
	ioport_init();
	fnd_init();
	interrupt_init();
	timer_init();
	
	while (1) {
		fnd_write_numbers(fnd_num);
		
		for(; note_idx < sizeof(m_notes)/2; note_idx++) {
			
			if(m_notes[note_idx] == XX) {sound_mute();} //
			else {sound_set_frequency(m_notes[note_idx]);}
			my_delay_ms(m_duration[note_idx] * music_tempo);
			
		}	
	
		
	}
}*/

