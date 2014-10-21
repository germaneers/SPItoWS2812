/*
 * Author: Nick (sqozz(AT)geekify.de
 * License: GNU GPL v2 (see LICENSE)
 * For more information about this, take a look at the first comment in SPItoWS2812.c
 */

#include "spi.h"
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

static uint8_t receivedData[(NUM_LEDS*3)];
static volatile uint16_t count = 0;
static uint8_t isDataAvailable = 0;

ISR(SPI_STC_vect) {
	if ( count < (NUM_LEDS*3) ) {
		receivedData[ count ] = SPDR;
		count++;
	}
}

// This is the interrupt handler for the CS line.
// in case of a falling edge, we prepare for the
// SPI transfer that is about to come in in 100uS.
// in case of an rising edge, we do some cleanup.
ISR(PCINT0_vect) {
	if (PINB & (1<<PB2)) {
		// rising edge
		isDataAvailable = 1;
	} else {
		// falling edge
		PORTB &= ~( 1<<PB1 );
		isDataAvailable = 0;
		count = 0;
	}
}

int8_t spi_slave_init() {
	PCMSK0 |= (1<<PCINT2);
	PCICR  |= (1<<PCIE0);
	/* Set MISO output, all others input */
	DDRB |= (1<<PB6);
	DDRB &= ~((1<<PB7)|(1<<PB5)|(1<<PB2));
	/* Enable SPI */
	SPCR = (1<<SPE) | (1<<SPIE); // enable SPI
	DDRC &= ~(1<<PC4);  // ACK_MOSI
	PORTC &= ~(1<<PC4);
	DDRC |= (1<<PC3); // ACK_MISO

	return 1;
}

uint8_t* spi_receive( ) {
	if ( isDataAvailable == 1) {
		isDataAvailable = 0;
		memset( receivedData + count, 0, (NUM_LEDS*3) - count );
		return receivedData;
	} else {
		return NULL;
	}
}
