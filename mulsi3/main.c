#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

static int uart_putchar(char c, FILE *stream) {
	UDR0 = c; // good enough for simavr
}

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

// Source: https://en.wikipedia.org/wiki/Xorshift
static uint32_t xorshift32_state = 1;
uint32_t xorshift32(void)
{
	uint32_t x = xorshift32_state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	xorshift32_state = x;
	return x;
}

long test_mulsi3(long a, long b);

int main(void) {
	// needed for printf
	stdout = &mystdout;

	// Iterate continuously, looking for mismatches.
	unsigned long n = 0;
	while (1) {
		long a = xorshift32();
		long b = xorshift32();

		if ((n % (1ul << 20)) == 0) {
			printf("%8lu: %ld * %ld\r\n", n, a, b);
		}
		n++;

		long actual = test_mulsi3(a, b);
		long expected = a * b;
		if (expected != actual) {
			printf("invalid result: %l * %l = %l (expected %l)\n", a, b, actual, expected);
		}
	}
	return 0;
}
