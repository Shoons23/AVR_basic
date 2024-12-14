

#include "board.h"
#include "fnd.h"

/* ----------------------------------------------------------------------------
 * initialize port for FND/LED interface
 * -------------------------------------------------------------------------- */
inline static void fnd_port_init(void)
{
    // configure output
    DDRC = 0xff;            // PORTC[7..0]
    DDRG = 0x07;            // PORTG[2..0]
    DDRB |= _BV(LED_COLOR);
}

/* ----------------------------------------------------------------------------
 * select FND to access
 * arguments
 *  - fnd_num: FND number (2 ~ 0)
 * -------------------------------------------------------------------------- */
inline static void fnd_select(uint8_t fnd_num)
{
    PORTG = fnd_num;
}

/* ----------------------------------------------------------------------------
 * deselect selected FND
 * -------------------------------------------------------------------------- */
inline static void fnd_deselect(void)
{
    PORTG = 0x07;
}

/* ----------------------------------------------------------------------------
 * initialize FND/LED
 * -------------------------------------------------------------------------- */
void fnd_init(void)
{
    fnd_port_init();
    fnd_clear_all();
    led_write(0xff);
}

/* ----------------------------------------------------------------------------
 * write FND 
 * arguments
 *  - fnd_num: FND number (2 ~ 0)
 *  - value: 1-byte data to write
 * -------------------------------------------------------------------------- */
void fnd_write(uint8_t fnd_num, uint8_t value)
{
    uint8_t sreg;
    
    sreg = SREG;            // save SREG
    cli();                  // disable interrupt to prevent shared-data problem

    fnd_select(fnd_num);
    PORTC = value;
    fnd_deselect();

    if(sreg&0x80)           // if global interrupt was enabled before executing cli()
        sei();              // enable interrupt        
}


/* ----------------------------------------------------------------------------
 * clear FND 
 * arguments
 *  - fnd_num: FND number (2 ~ 0)
 * -------------------------------------------------------------------------- */
inline void fnd_clear(uint8_t fnd_num)
{
    fnd_write(fnd_num, 0);
}

/* ----------------------------------------------------------------------------
 * clear all FNDs 
 * -------------------------------------------------------------------------- */
void fnd_clear_all(void)
{
    fnd_write(0, 0);
    fnd_write(1, 0);
	fnd_write(2, 0);
}
/* ----------------------------------------------------------------------------
 * display a hexadecimal number on an FND 
 * arguments
 *  - fnd_num: FND number (0 ~ 2)
 *  - num: hexadecimal number to display on FND (0 ~ 0xf)
 *  - dot_on: dot is turned on if 1, or turned off otherwise
 * -------------------------------------------------------------------------- */
void fnd_write_number(uint8_t fnd_num, uint8_t num, uint8_t dot_on)
{
    static uint8_t num_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f,
                                  0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
    uint8_t value;
    
    value = num_code[num] | (dot_on<<7);
    fnd_write(fnd_num, value);    
}


void fnd_write_numbers(uint16_t num)
{
	uint8_t num_100, num_10, num_1;
	
	num_100 = num / 100;
	num_10 = num / 10 % 10;
	num_1 = num % 10;

	fnd_write_number(0, num_1, 0);
	fnd_write_number(1, num_10, 0);
	fnd_write_number(2, num_100, 0);
}

void fnd_write_numbers_ultra(uint16_t num){
    uint8_t dot_off = 0x00;
    uint8_t value_u4 = num  % 10;
	uint8_t value_u6 = (num / 10) % 10;
	uint8_t value_u8 = num / 100;
	
	if(num < 10){
		fnd_write_number(0, value_u4, dot_off);
		fnd_write(1, 0);
		fnd_write(2, 0);
	}
	else if(num < 100) {
		fnd_write_number(0, value_u4, dot_off);
		fnd_write_number(1, value_u6, dot_off);
		}
	else {
	    fnd_write_number(0, value_u4, dot_off);
	    fnd_write_number(1, value_u6, dot_off);
	    fnd_write_number(2, value_u8, dot_off);
	}
}

/* ----------------------------------------------------------------------------
 * write LED 
 * arguments
 *  - value: 1-byte data to write
 * -------------------------------------------------------------------------- */
void led_write(uint8_t value)
{
    uint8_t sreg;
    
    sreg = SREG;            // save SREG
    cli();                  // disable interrupt to prevent shared-data problem

    fnd_select(3);
    PORTC = value;
    fnd_deselect();

    if(sreg&0x80)           // if global interrupt was enabled before executing cli()
        sei();              // enable interrupt        
}
