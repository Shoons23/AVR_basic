/*
 * ADC.c
 *
 * Created: 2024-12-10 오전 10:06:22
 * Author : tshoon
 */ 

#include <avr/io.h>

void adc_init(void){
	ADCSRA = _BV(ADEN) | _BV(ADIE);
	ADMUX = _BV(REFS0);// 0 ~ AVCC
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);// set a prescaler - "50 KHz < ADC clock < 200 KHz" : 128 
	ADCSRB &= ~(_BV(ADTS2) | _BV(ADTS1) | _BV(ADTS0));  // Free Running mode
	ADCSRA |= _BV(ADSC); // conversion start
}
uint16_t adc_get_result(uint8_t channel_num){
	// The parameter 'channel_num' is a value between 0 and 7, representing the ADC input channel.
	// Configure the ADMUX register to select the appropriate ADC channel (without altering other bits).
	ADMUX = (ADMUX & 0xF0) | (channel_num & 0x0F);

	ADCSRA = _BV(ADSC); // Start the ADC conversion.
	while (!(ADCSRA & _BV(ADIF))); // Wait until the ADC conversion is complete.
	ADCSRA = _BV(ADIF); // Clear the ADIF flag by writing 1 to it.

	return ADC; 
}

int main(void)
{
    
    while (1) 
    {
    }
}

