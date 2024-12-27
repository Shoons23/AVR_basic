/*
 * sound.c
 *
 * Created: 11-15(금) 오후 11:06:46
 *  Author: Moon
 */ 

/*
 * sound.c
 *
 * modified: 2024-11-20 오전 10:35:57
 *  Author: tshoon
 */ 

#include "board.h"

/* ----------------------------------------------------------------------------
 * set output frequency OC3A of Timer3
 * arguments
 *  - freq_hz: the frequency of output pulse
 *    (minimum available value of freq_hz: 16 Hz)
 * -------------------------------------------------------------------------- */
void sound_set_frequency(uint16_t freq_hz){
	OCR3A = F_CPU/(2*8*freq_hz)- 1; // compare match setting
	TCNT3 = 0; // Timer3 counter reset (if not, sound breaks out temporaily)
	TCCR3B |= _BV(CS31); // Timer3 prescaler : 8
}

/* ----------------------------------------------------------------------------
 * mute output
 * -------------------------------------------------------------------------- */
void sound_mute(void){
    TCCR3B &= ~(_BV(CS32)|_BV(CS31)|_BV(CS30)); // no clock source: stop 
    
    if(PINE &_BV(SOUND_OUT))        // if OC3A is 'H', toggle it                     
        TCCR3C = _BV(FOC3A);    
}
