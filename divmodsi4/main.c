#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>

static int uart_putchar(char c, FILE *stream) {
	UDR0 = c; // good enough for simavr
	return 0;
}

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

// Source: https://en.wikipedia.org/wiki/Xorshift
static uint32_t xorshift32(void) {
	static uint32_t state = 1;
	uint32_t x = state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	state = x;
	return x;
}

// The result is returned as a 8 byte value, consisting of two 32-bit values
// (the quotient and the remainder).
union result {
	uint64_t n;
	struct {
		uint32_t q;
		uint32_t r;
	};
};

uint64_t test_udivmodsi4(uint32_t a, uint32_t b);
uint64_t test_divmodsi4(int32_t a, int32_t b);

int main(void) {
	// needed for printf
	stdout = &mystdout;

	// Iterate continuously, looking for mismatches.
	uint32_t n = 0;
	while (1) {
		uint32_t a = xorshift32();
		uint32_t b = xorshift32();
		if (b == 0) {
			continue;
		}

		// Print progress once in a while.
		if ((n % (1ul << 20)) == 0) {
			printf("%8lu: %lu / %lu\r\n", n, a, b);
		}
		n++;

		// Test unsigned division.
		union result res;
		res.n = test_udivmodsi4(a, b);
		uint32_t q1 = a / b;
		uint32_t r1 = a % b;
		uint32_t q2 = res.q;
		uint32_t r2 = res.r;
		if ((q1 != q2) || (r1 != r2)) {
			printf("fail: %10lu / %10lu = %10lu %10lu (expected %lu %lu)\r\n", a, b, q2, r2, q1, r1);
		} else {
			//printf("ok:   %10lu / %10lu = %10lu %10lu\r\n", a, b, q2, r2);
		}

		// Test signed division.
		int32_t as = a;
		int32_t bs = b;
		res.n = test_divmodsi4(a, b);
		int32_t q1s = as / bs;
		int32_t r1s = as % bs;
		int32_t q2s = res.q;
		int32_t r2s = res.r;
		if ((q1s != q2s) || (r1s != r2s)) {
			printf("fail: %11ld / %11ld = %11ld %11ld (expected %ld %ld)\r\n", as, bs, q2s, r2s, q1s, r1s);
		} else {
			//printf("ok:   %11ld / %11ld = %11ld %11ld\r\n", as, bs, q2s, r2s);
		}
	}
	return 0;
}
