/*
 * ADC.c
 *
 * Created: 2024-12-10 오전 10:06:22
 * Author : tshoon
 */ 

#include <avr/io.h>
#include "board.h"
#include "fnd.h"
#include "led_pattern.h"
#include <stdio.h>
#include "uart.h"

volatile uint16_t adc_value= 0;

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
 	
	uart_init();
    adc_init();
	fnd_init();
	interrupt_init();
	
	//fdevopen(uart_putch, uart_getch);
	
    while (1) 
    {

		led_write(led_pattern[i++%8]);
		_delay_ms(250);		
		
    }
}



//4.
//int main(void)
//{
	//uint8_t i= 0;
	//
	//uart_init();
	//adc_init();
	//fnd_init();
	//interrupt_init();
	//
	//fdevopen(uart_putch, uart_getch);
	//
	//while (1)
	//{
		//if(PIND & _BV(SW3)){
			//printf("ADC value: %x\r\n", adc_get_result(1));
			//_delay_ms(100);
		//}
	//}
//}