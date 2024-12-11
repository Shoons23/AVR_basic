/*
 * ADC.c
 *
 * Created: 2024-12-10 오전 10:06:22
 * Author : tshoon
 */ 

#include <avr/io.h>
#include "board.h"
#include "fnd.h"
#include <stdio.h>
#include "uart.h"

uint16_t adc_value= 0;

ISR(USART0_RX_vect){
	UDR0 = UDR0;  
	if(UDR0 == 'a'){
		ADCSRA |= _BV(ADSC);
		//printf("ADC started!\r\n");  
	}
}
//ISR(USART0_RX_vect){
	//uint8_t rx_data = UDR0;
	//if(rx_data == 'a'){
		//ADCSRA |= _BV(ADSC);
	//}
//}
ISR(ADC_vect){
	adc_value = ADC;
	fnd_write_numbers(adc_value);
	//printf("ADC_value : %x\r\n", adc_value);
}
void ioport_init(void){
	DDRB |= _BV(LED_COLOR);
	DDRC |= _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTC |= _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4);
	PORTE |= _BV(SW2);
	PORTD |= _BV(SW3);
}
void interrupt_init(void){
	sei();
}

void adc_init(void){
	ADCSRA = _BV(ADEN) | _BV(ADIE);
	ADMUX = _BV(REFS0);
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); 
	ADCSRA |= _BV(ADSC);  
}
uint16_t adc_get_result(uint8_t channel_num){

	ADMUX = (ADMUX & 0xE0) | channel_num ;

	ADCSRA |= _BV(ADSC); 
	while (!(ADCSRA & _BV(ADIF)));
	ADCSRA |= _BV(ADIF); 

	return ADC; 
}

int main(void)
{
	 uint8_t i= 0;
	
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
	 	
    adc_init();
	interrupt_init();
	fnd_init();
	uart_init();
	
	
	//fdevopen(uart_putch, uart_getch);
	
    while (1) 
    {

		led_write(led_pattern[i++%8]);
		_delay_ms(250);		
		
    }
}



