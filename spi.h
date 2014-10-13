/*
 * Author: Nick (sqozz(AT)geekify.de
 * License: GNU GPL v2 (see LICENSE)
 * For more information about this, take a look at the first comment in SPItoWS2812.c
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <avr/io.h>

int8_t spi_slave_init();
uint8_t* spi_receive( );

#endif // SPI_H_

