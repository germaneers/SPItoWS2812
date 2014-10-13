Description
===========

A simple program for a ATmega328p. It receives SPICommands and sends them directly into an WS2812-LED-Strip.

Limitations
===========

So far, this program can receive 999 bytes which is equivalent to 333 RGB-LED's ( 1 Byte for each color ).
This Limitation is due to the limited RAM on the ATmega. Ther should be more possible, but for now 333 LED's are just enough. Feel free to test out the limitations or optimizing the code and after that do not forget so send a pull request :)

Usage
===========
coming soon™…

Credits
===========
Struppi: For his SPI-slave and master code.
[Bytewerk Rhodecode](http://rhodecode.bytewerk.org/Mikrocontroller/RGByteClock/rgbyteclock-firmware)

Tim/cpldcpu: For his simle and light WS2812 library 
[cpldcpu/light_ws2812](https://github.com/cpldcpu/light_ws2812)
