firmware.elf: main.c mulsi3.S Makefile
	avr-gcc -o firmware.elf main.c mulsi3.S -Os -mmcu=atmega1284p

.PHONY: test
test: firmware.elf
	simavr -m atmega1284p -f 20000000 ./firmware.elf
