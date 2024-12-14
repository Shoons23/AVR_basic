/*
 * led_pattern.h
 *
 * Created: 2024-11-27 오후 3:06:15
 *  Author: tshoon
 */ 


#ifndef LED_PATTERN_H_
#define LED_PATTERN_H_

uint8_t led_pattern[] = {
	_BV(LED1) | _BV(LED8),
	_BV(LED1) | _BV(LED2) | _BV(LED7) | _BV(LED8),
	_BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED6) | _BV(LED7) | _BV(LED8),
	0xFF,
	_BV(LED2) | _BV(LED3) | _BV(LED4) | _BV(LED5) | _BV(LED6) | _BV(LED7),
	_BV(LED3) | _BV(LED4) | _BV(LED5) | _BV(LED6),
	_BV(LED4) | _BV(LED5),
	0x00
};





#endif /* LED_PATTERN_H_ */