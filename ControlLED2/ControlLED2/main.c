/*
 * ControlLED2.c
 *
 * Created: 2024-12-10 오후 6:16:58
 * Author : tshoon
 */ 

#include <avr/io.h>
#include "board.h"
#include <util/delay.h>

uint8_t switch_hit(void);
uint8_t switch_hit2(void);

// 6. Program to change direction when switch is pressed
int main(void)
{
	uint8_t led_index = 0;
	uint8_t direction_index = 0;
	
	// Define LED patterns and direction array
	const uint8_t LED_PATTERNS[4] = {
		0x0C,   // Pattern 1: LED1,2 ON 
		0x09,   // Pattern 2: LED1,4 ON 
		0x03,   // Pattern 3: LED3,4 ON 
		0x06    // Pattern 4: LED2,3 ON 
	};
	const uint8_t DIRECTION[2] = {0, 1};  // 0: Forward(++), 1: Reverse(--)
	
	// Initialize LED ports
	DDRC = _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTC = _BV(LED3) | _BV(LED4);  // LED3, LED4 OFF initially
	
	// Enable pull-up resistor for SW2
	PORTE |= _BV(SW2);
	PORTD |= _BV(SW3);
	
	
	while (1)
	{
		if (switch_hit()) {
			direction_index = !direction_index;  // Toggle direction
		}
		
		if (DIRECTION[direction_index]) {
			led_index = (led_index + 3) % 4;    // Reverse direction
		}
		else {
			led_index = (led_index + 1) % 4;    // Forward direction
		}
		
		// Update LED status
		PORTC = (PORTC & 0xF0) | LED_PATTERNS[led_index];
		
		_delay_ms(500);  // 0.5 second delay
	}
}

// Function that returns 1 when switch is pressed
uint8_t switch_hit(void) {
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

// Function that returns 1 when switch is released
uint8_t switch_hit2(void) {
	static uint8_t prev_state = _BV(SW2);
	uint8_t cur_state;
	
	cur_state = PINE & _BV(SW2);
	if(prev_state != cur_state) {
		prev_state = cur_state;
		if(cur_state) return 1;
		else return 0;
	}
	else
	return 0;
}