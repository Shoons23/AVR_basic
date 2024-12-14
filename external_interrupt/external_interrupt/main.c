/*
 * external_interrupt.c
 
 * Created: 2024-10-23 오전 9:44:52
 * Author : tshoons
 */ 



#include "board.h"
#include "fnd.h"

uint16_t fnd_num = 0;
uint8_t i = 0;

ISR(INT3_vect){
	fnd_num = (fnd_num+1000-1)%1000;
	fnd_write_numbers_ultra(fnd_num);
}
// For sw2 bounce
ISR(INT7_vect){
	static uint8_t old_state = 1;
	uint8_t new_state = (PINE & _BV(SW2)) ? 1 : 0;
	
	if(old_state != new_state) {  // 상태가 변했을 때
		if(new_state == 0) {      // 눌렸을 때
			fnd_num = (fnd_num+1)%1000;
			} else {                  // 떼졌을 때
			led_write(0x00);
		}
		old_state = new_state;
	}
}
//ISR(INT7_vect){
    //if(!(PINE & _BV(SW2))) { 
        //fnd_num = (fnd_num+1)%1000;
        //fnd_write_numbers_ultra(fnd_num);
    //} else {                  
        //led_write(0x00);
    //}
//}


void ioport_init(){
	DDRC |= _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTC |= _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTE |= _BV(SW2);
	PORTD |= _BV(SW3);
}

void interrupt_init(){
	EICRA = _BV(ISC31);      // INT3 falling edge
	// EICRB = _BV(ISC71);    // INT7 LOW state
	EIMSK = _BV(INT7) | _BV(INT3);
	sei();
}

int main(void) {
	uint16_t led_pattern[] = {
		_BV(LED1) | _BV(LED8),
		_BV(LED1) | _BV(LED2) | _BV(LED7) | _BV(LED8),
		_BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED6) | _BV(LED7) | _BV(LED8),
		0xFF,
		_BV(LED2) | _BV(LED3) | _BV(LED4) | _BV(LED5) | _BV(LED6) | _BV(LED7),
		_BV(LED3) | _BV(LED4) | _BV(LED5) | _BV(LED6),
		_BV(LED4) | _BV(LED5),
		0x00
	};
	
	ioport_init();
	interrupt_init();
	fnd_init();
	
	while (1) {
		fnd_write_numbers_ultra(fnd_num);
		led_write(led_pattern[i++%8]);
		_delay_ms(250);
	}
}







