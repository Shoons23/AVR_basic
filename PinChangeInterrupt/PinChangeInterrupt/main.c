/*
 * PinChangeInterrupt.c
 *
 * Created: 2024-11-06 오후 1:05:31
 * Author : tshoon
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "board.h"
#include "fnd.h"

uint16_t fnd_num;
uint8_t led_pattern[] = {0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x3c, 0x18, 0x00};
uint8_t led_idx;

uint8_t prev_sw3;
uint8_t prev_sw4;

ISR(PCINT0_vect){
	uint8_t curr_sw3 = PINB&_BV(PB5);
	uint8_t curr_sw4 = PINB&_BV(PB6);
	
	if(PINB&_BV(PB5)){
		if(prev_sw3 != curr_sw3)
			fnd_num = (fnd_num+1000-1)%1000;
	}
	
	if(PINB&_BV(PB6)){
		if(prev_sw4 != curr_sw4)
			fnd_num = (fnd_num+1)%1000;	
	}
	prev_sw3 = curr_sw3;
	prev_sw4 = curr_sw4;
}

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

int main(void){ 

	ioport_init();
	interrupt_init();
	fnd_init();
	
	led_write(0xff);
	fnd_write_numbers(0);
    
	while (1) 
    {
		fnd_write_numbers(fnd_num);
		led_write(led_pattern[led_idx++%8]);
		_delay_ms(250);
    }
}

