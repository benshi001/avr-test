firmware.elf: main.c udivmodsi4.S divmodsi4.S Makefile
	avr-gcc -o firmware.elf main.c udivmodsi4.S divmodsi4.S -Os -mmcu=atmega1284p -Wall -Werror

.PHONY: test
test: firmware.elf
	simavr -m atmega1284p -f 20000000 ./firmware.elf
