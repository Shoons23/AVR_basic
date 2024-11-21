/*
 * ----------------------------------------------------------------------------
 *          Header file for ATmega1281 board
 * ----------------------------------------------------------------------------
 */


#ifndef BOARD_H
#define BOARD_H

#define F_CPU               16000000L   // 16 MHz
#define FIRMWARE_VERSION    0x0001      // firmware version

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// PORTA

// PORTB
#define LED_COLOR   PB4         // output: LED color control

// PORTC
#define LED1        PC0         // output: LED 1~8
#define LED2        PC1         
#define LED3        PC2         
#define LED4        PC3        
#define LED5        PC4
#define LED6        PC5
#define LED7        PC6         
#define LED8        PC7         

// PORTD
#define SW3         PD3         // input: switch (internal pull-up resistor required)
#define SW4         PD4

// PORTE
#define SOUND_OUT   PE3
#define SW2         PE7         // input: switch (internal pull-up resistor required)

// PORTF

// MACRO functions

#endif

