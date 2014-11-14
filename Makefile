PRG            = SPItoWS2812
OBJ            = SPItoWS2812.o spi.o
F_CPU          = 8000000UL
MCU_TARGET     = atmega328
NUM_LEDS       = 8
OPTIMIZE       = -Os

DEFS           =
LIBS           =

CC             = avr-gcc

override CFLAGS        = -g -Wall $(OPTIMIZE) -DF_CPU=$(F_CPU) -std=gnu99 -mmcu=$(MCU_TARGET) $(DEFS) -DNUM_LEDS=$(NUM_LEDS)
override LDFLAGS       = -Wl,-Map,$(PRG).map

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump
SIZE           = avr-size -A


all: $(PRG).hex $(PRG).bin


$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo
	@$(SIZE) $@ 
	@echo

clean:
	rm -rf *.o $(PRG).elf $(PRG).bin $(PRG).hex *.eps *.png *.pdf *.bak 
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

hex:  $(PRG).hex
bin:  $(PRG).bin

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

prg: $(PRG).bin
	sudo avrdude -p m328 -c jtag3isp -U flash:w:$(PRG).bin
