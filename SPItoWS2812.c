/*
 * Simple SPI slave, that converts 999 Bytes into 333 RGB-LEDs and sends it to a WS2812-LED-Strip.
 * This program is designed and tested on a ATmega328P @ 16MHz
 * Author: Nick (sqozz(AT)geekify.de)
 * Uses code from: Tim (WS2812-Lib https://github.com/cpldcpu/light_ws2812/blob/master/light_ws2812_AVR/Light_WS2812/light_ws2812.c)
 *                 Struppi (SPI-slave http://rhodecode.bytewerk.org/Mikrocontroller/RGByteClock/rgbyteclock-firmware)
 * License: GNU GPL v2 (see LICENSE)
 */

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include "light_ws2812.c"
#include "spi.h"

int main( ) {
	DDRB |= ( 1<<PB1 );
	PORTB |= ( 1<<PB1 );
	spi_slave_init();
	sei();
	uint8_t* data;

	while ( 1 ) {
		//data != NULL if there is data in the SPI-buffer
		data = spi_receive( );
		if ( data ) {
			//Disable interrupts for more performance
			cli();
			//Write received data to the ledstrip
			//Technically this function wants a RGB-struct but casts it internal to an uint8 array.
			//So we simply ignore the struct to make it easier for us and to save RAM on the ATmega.
			ws2812_setleds( data, 333 );
			//Enable interrupts again
			sei();
			//Set ready to receive to get data
			PORTB |= ( 1<<PB1 );
		}
	}
}
