Description
===========

A simple program for a ATmega328p. It receives SPICommands and sends them directly into an WS2812-LED-Strip.

Limitations
===========

So far, this program can receive 999 bytes which is equivalent to 333 RGB-LEDs ( 1 Byte for each color ).
This Limitation is due to the limited RAM on the ATmega. There should be more possible, but for now 333 LEDs are just enough. Feel free to test out the limitations or optimize the code and after that do not forget so send a pull request :)

Also the LED order is a little bit weird. The light_ws2811 library wants green, red, blue as order. But i don't care about this. This lib has taken away enouth work from me!

If you found any bugs or errors, please fill a bugreport on GitHub or submit a pull request if you fix it on your own.

Usage
===========
The Makefile is optimized for flashing the program to a ATMega328p @ 16MHz with a Arduino bootloader attached to /dev/ttyUSB0.
To flash this program to an ATMega with this properties simply type in the directory:
```shell
$ make prg
```

For the SPI-port configuration take a look at the spi_slave_init() funtion in the spi.c file.
If you want to send data to the led strip over spi, send a uint8 array to the "SPItoWS2812" ATMega.
Currently it suppots 333 LEDs which means you need to send 999 bytes (3 bytes per LED). If the array is smaller than 999 elements, the remaining LEDs will be filled with 0x00.
Because of the way the light_ws2812 library works, the array must contain the LED order green, red, blue.

A little example:
```shell
uint8_t data[999];

//First LED
data[0] = 0x00;
data[1] = 0xFF;
data[2] = 0x00;

//Second LED
data[3] = 0xFF;
data[4] = 0x00;
data[5] = 0x00;

//Third LED
data[6] = 0x00;
data[7] = 0x00;
data[8] = 0xFF;

//Fourth LED
data[9] = 0xFF;
data[10] = 0xFF;
data[11] = 0xFF;
```

If you whould send the data-array over SPI to the "SPItoWS2812" ATMega, the first LED whould be red, the second, green, the third blue and the fourth white. Every LED after that 4 whould be black/off.

Credits
===========
Struppi: For his SPI-slave and master code.
[Bytewerk Rhodecode](http://rhodecode.bytewerk.org/Mikrocontroller/RGByteClock/rgbyteclock-firmware)

Tim/cpldcpu: For his simple and light WS2812 library 
[cpldcpu/light_ws2812](https://github.com/cpldcpu/light_ws2812)
