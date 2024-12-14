/*
 * 7Segment_LED.c
 *
 * Created: 2024-12-02 오후 5:33:03
 * Author : tshoon
 */

#include <avr/io.h>
#include "board.h"
#include "fnd.h"

uint8_t switch_hit(void){
	static uint8_t prev_state = _BV(SW2);
	uint8_t cur_state;
	
	cur_state = PINE & _BV(SW2);
	if(prev_state != cur_state) {
		prev_state = cur_state;
		if(!cur_state) return 1;
		else return 0;
	}
	else
		return 0;
}
uint8_t switch_hit_sw3(void){
	static uint8_t prev_state = _BV(SW3);
	uint8_t cur_state;
	
	cur_state = PIND & _BV(SW3);
	if(prev_state != cur_state) {
		prev_state = cur_state;
		if(!cur_state) return 1;
		else return 0;
	}
	else
	return 0;
}

void ioport_init(void){
	DDRB |= _BV(LED_COLOR);
	DDRC |= _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTE |= _BV(SW2);
	PORTD |= _BV(SW3) | _BV(SW4) | _BV(SW5);
}

// mode 0 : fnd stop - mode 1 : fnd_value increase 

int main(void)
{
	uint16_t fnd_num= 0;
	int8_t mode = 0;
	
	ioport_init();
	fnd_init();
	
	led_write(0xff);
	
	while (1)
	{
		if(switch_hit()){
			mode = !mode;
		}
		
		if(switch_hit_sw3()){
			PORTB ^= _BV(LED_COLOR);
			fnd_num = 0;
		}

		if(mode){
			fnd_write_numbers_ultra(fnd_num++);
			led_write(0xff);
			_delay_ms(100);
			}else{
			fnd_write_numbers_ultra(fnd_num);
			led_write(0x00);
		}
		
		if(fnd_num == 1000){
			fnd_num = 0;
		}
		
	}
}


