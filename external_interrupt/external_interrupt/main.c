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
	fnd_write_numbers(fnd_num);
}
ISR(INT7_vect){
	if(!(PINE&_BV(SW2)))
		fnd_num = (fnd_num+1)%1000;
	else
		i = 7;
}

void ioport_init(){
	DDRC |= _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTC |= _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTE |= _BV(SW2);
}
void interrupt_init(){
	EICRA = _BV(ISC31); // External Interrupt Control Register A
	EICRB = _BV(ISC71); // External Interrupt Control Register B
	EIMSK = _BV(INT7) | _BV(INT3); // External Interrupt Mask Register
	sei(); // global interrupt flag set
}

int main(void) { 
	 uint16_t led_pattern[] = {
		 _BV(LED1) | _BV(LED8),
		 _BV(LED1) | _BV(LED2) | _BV(LED7) | _BV(LED8),
		 _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED6) | _BV(LED7) | _BV(LED8),
		 0xFF,
		 _BV(LED2) | _BV(LED3) | _BV(LED4) | _BV(LED5) | _BV(LED6) | _BV(LED7),
		 _BV(LED3) | _BV(LED4) | _BV(LED5),
		 _BV(LED4) | _BV(LED5),
		 0x00
	 };

	 ioport_init();
	 interrupt_init();
	 fnd_init();

	while (1)
	{
		fnd_write_numbers(fnd_num);
		led_write(led_pattern[i++%8]);
		_delay_ms(250);
	}
}



