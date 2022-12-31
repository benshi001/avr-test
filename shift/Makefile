CLANG ?= clang

firmware.elf: main.c shift.o Makefile
	avr-gcc -o firmware.elf main.c shift.o -Os -mmcu=atmega1284p

shift.o: shift.c Makefile
	$(CLANG) -c -o shift.o shift.c --target=avr -mmcu=atmega1284p -ffunction-sections -Os

.PHONY: test
test: firmware.elf
	simavr -m atmega1284p -f 20000000 ./firmware.elf

.PHONY: clean
clean:
	rm *.o firmware.elf
