#include <avr/io.h>
#include <avr/sleep.h>
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

uint32_t shl32_1(uint32_t x);
uint32_t shl32_2(uint32_t x);
uint32_t shl32_3(uint32_t x);
uint32_t shl32_4(uint32_t x);
uint32_t shl32_5(uint32_t x);
uint32_t shl32_6(uint32_t x);
uint32_t shl32_7(uint32_t x);
uint32_t shl32_8(uint32_t x);
uint32_t shl32_9(uint32_t x);
uint32_t shl32_10(uint32_t x);
uint32_t shl32_11(uint32_t x);
uint32_t shl32_12(uint32_t x);
uint32_t shl32_13(uint32_t x);
uint32_t shl32_14(uint32_t x);
uint32_t shl32_15(uint32_t x);
uint32_t shl32_16(uint32_t x);
uint32_t shl32_17(uint32_t x);
uint32_t shl32_18(uint32_t x);
uint32_t shl32_19(uint32_t x);
uint32_t shl32_20(uint32_t x);
uint32_t shl32_21(uint32_t x);
uint32_t shl32_22(uint32_t x);
uint32_t shl32_23(uint32_t x);
uint32_t shl32_24(uint32_t x);
uint32_t shl32_25(uint32_t x);
uint32_t shl32_26(uint32_t x);
uint32_t shl32_27(uint32_t x);
uint32_t shl32_28(uint32_t x);
uint32_t shl32_29(uint32_t x);
uint32_t shl32_30(uint32_t x);
uint32_t shl32_31(uint32_t x);

uint32_t lshr32_1(uint32_t x);
uint32_t lshr32_2(uint32_t x);
uint32_t lshr32_3(uint32_t x);
uint32_t lshr32_4(uint32_t x);
uint32_t lshr32_5(uint32_t x);
uint32_t lshr32_6(uint32_t x);
uint32_t lshr32_7(uint32_t x);
uint32_t lshr32_8(uint32_t x);
uint32_t lshr32_9(uint32_t x);
uint32_t lshr32_10(uint32_t x);
uint32_t lshr32_11(uint32_t x);
uint32_t lshr32_12(uint32_t x);
uint32_t lshr32_13(uint32_t x);
uint32_t lshr32_14(uint32_t x);
uint32_t lshr32_15(uint32_t x);
uint32_t lshr32_16(uint32_t x);
uint32_t lshr32_17(uint32_t x);
uint32_t lshr32_18(uint32_t x);
uint32_t lshr32_19(uint32_t x);
uint32_t lshr32_20(uint32_t x);
uint32_t lshr32_21(uint32_t x);
uint32_t lshr32_22(uint32_t x);
uint32_t lshr32_23(uint32_t x);
uint32_t lshr32_24(uint32_t x);
uint32_t lshr32_25(uint32_t x);
uint32_t lshr32_26(uint32_t x);
uint32_t lshr32_27(uint32_t x);
uint32_t lshr32_28(uint32_t x);
uint32_t lshr32_29(uint32_t x);
uint32_t lshr32_30(uint32_t x);
uint32_t lshr32_31(uint32_t x);

uint32_t ashr32_1(uint32_t x);
uint32_t ashr32_2(uint32_t x);
uint32_t ashr32_3(uint32_t x);
uint32_t ashr32_4(uint32_t x);
uint32_t ashr32_5(uint32_t x);
uint32_t ashr32_6(uint32_t x);
uint32_t ashr32_7(uint32_t x);
uint32_t ashr32_8(uint32_t x);
uint32_t ashr32_9(uint32_t x);
uint32_t ashr32_10(uint32_t x);
uint32_t ashr32_11(uint32_t x);
uint32_t ashr32_12(uint32_t x);
uint32_t ashr32_13(uint32_t x);
uint32_t ashr32_14(uint32_t x);
uint32_t ashr32_15(uint32_t x);
uint32_t ashr32_16(uint32_t x);
uint32_t ashr32_17(uint32_t x);
uint32_t ashr32_18(uint32_t x);
uint32_t ashr32_19(uint32_t x);
uint32_t ashr32_20(uint32_t x);
uint32_t ashr32_21(uint32_t x);
uint32_t ashr32_22(uint32_t x);
uint32_t ashr32_23(uint32_t x);
uint32_t ashr32_24(uint32_t x);
uint32_t ashr32_25(uint32_t x);
uint32_t ashr32_26(uint32_t x);
uint32_t ashr32_27(uint32_t x);
uint32_t ashr32_28(uint32_t x);
uint32_t ashr32_29(uint32_t x);
uint32_t ashr32_30(uint32_t x);
uint32_t ashr32_31(uint32_t x);

int main(void) {
	// needed for printf
	stdout = &mystdout;

	// Iterate continuously, looking for mismatches.
	unsigned long n = 0;
	for (uint8_t i=0; i<255; i++) {
		unsigned long x = xorshift32();

		//printf("testing: %lu\r\n", x);
		n++;

		if (shl32_1(x) != x << 1) { printf("mismatch: 0x%08lx << 1 (got 0x%08lx)\n", x, shl32_1(x)); }
		if (shl32_2(x) != x << 2) { printf("mismatch: 0x%08lx << 2 (got 0x%08lx)\n", x, shl32_2(x)); }
		if (shl32_3(x) != x << 3) { printf("mismatch: 0x%08lx << 3 (got 0x%08lx)\n", x, shl32_3(x)); }
		if (shl32_4(x) != x << 4) { printf("mismatch: 0x%08lx << 4 (got 0x%08lx)\n", x, shl32_4(x)); }
		if (shl32_5(x) != x << 5) { printf("mismatch: 0x%08lx << 5 (got 0x%08lx)\n", x, shl32_5(x)); }
		if (shl32_6(x) != x << 6) { printf("mismatch: 0x%08lx << 6 (got 0x%08lx)\n", x, shl32_6(x)); }
		if (shl32_7(x) != x << 7) { printf("mismatch: 0x%08lx << 7 (got 0x%08lx)\n", x, shl32_7(x)); }
		if (shl32_8(x) != x << 8) { printf("mismatch: 0x%08lx << 8 (got 0x%08lx)\n", x, shl32_8(x)); }
		if (shl32_9(x) != x << 9) { printf("mismatch: 0x%08lx << 9 (got 0x%08lx)\n", x, shl32_9(x)); }
		if (shl32_10(x) != x << 10) { printf("mismatch: 0x%08lx << 10 (got 0x%08lx)\n", x, shl32_10(x)); }
		if (shl32_11(x) != x << 11) { printf("mismatch: 0x%08lx << 11 (got 0x%08lx)\n", x, shl32_11(x)); }
		if (shl32_12(x) != x << 12) { printf("mismatch: 0x%08lx << 12 (got 0x%08lx)\n", x, shl32_12(x)); }
		if (shl32_13(x) != x << 13) { printf("mismatch: 0x%08lx << 13 (got 0x%08lx)\n", x, shl32_13(x)); }
		if (shl32_14(x) != x << 14) { printf("mismatch: 0x%08lx << 14 (got 0x%08lx)\n", x, shl32_14(x)); }
		if (shl32_15(x) != x << 15) { printf("mismatch: 0x%08lx << 15 (got 0x%08lx)\n", x, shl32_15(x)); }
		if (shl32_16(x) != x << 16) { printf("mismatch: 0x%08lx << 16 (got 0x%08lx)\n", x, shl32_16(x)); }
		if (shl32_17(x) != x << 17) { printf("mismatch: 0x%08lx << 17 (got 0x%08lx)\n", x, shl32_17(x)); }
		if (shl32_18(x) != x << 18) { printf("mismatch: 0x%08lx << 18 (got 0x%08lx)\n", x, shl32_18(x)); }
		if (shl32_19(x) != x << 19) { printf("mismatch: 0x%08lx << 19 (got 0x%08lx)\n", x, shl32_19(x)); }
		if (shl32_20(x) != x << 20) { printf("mismatch: 0x%08lx << 20 (got 0x%08lx)\n", x, shl32_20(x)); }
		if (shl32_21(x) != x << 21) { printf("mismatch: 0x%08lx << 21 (got 0x%08lx)\n", x, shl32_21(x)); }
		if (shl32_22(x) != x << 22) { printf("mismatch: 0x%08lx << 22 (got 0x%08lx)\n", x, shl32_22(x)); }
		if (shl32_23(x) != x << 23) { printf("mismatch: 0x%08lx << 23 (got 0x%08lx)\n", x, shl32_23(x)); }
		if (shl32_24(x) != x << 24) { printf("mismatch: 0x%08lx << 24 (got 0x%08lx)\n", x, shl32_24(x)); }
		if (shl32_25(x) != x << 25) { printf("mismatch: 0x%08lx << 25 (got 0x%08lx)\n", x, shl32_25(x)); }
		if (shl32_26(x) != x << 26) { printf("mismatch: 0x%08lx << 26 (got 0x%08lx)\n", x, shl32_26(x)); }
		if (shl32_27(x) != x << 27) { printf("mismatch: 0x%08lx << 27 (got 0x%08lx)\n", x, shl32_27(x)); }
		if (shl32_28(x) != x << 28) { printf("mismatch: 0x%08lx << 28 (got 0x%08lx)\n", x, shl32_28(x)); }
		if (shl32_29(x) != x << 29) { printf("mismatch: 0x%08lx << 29 (got 0x%08lx)\n", x, shl32_29(x)); }
		if (shl32_30(x) != x << 30) { printf("mismatch: 0x%08lx << 30 (got 0x%08lx)\n", x, shl32_30(x)); }
		if (shl32_31(x) != x << 31) { printf("mismatch: 0x%08lx << 31 (got 0x%08lx)\n", x, shl32_31(x)); }

		if (lshr32_1(x) != x >> 1) { printf("mismatch: 0x%08lx >> 1 (got 0x%08lx)\n", x, lshr32_1(x)); }
		if (lshr32_2(x) != x >> 2) { printf("mismatch: 0x%08lx >> 2 (got 0x%08lx)\n", x, lshr32_2(x)); }
		if (lshr32_3(x) != x >> 3) { printf("mismatch: 0x%08lx >> 3 (got 0x%08lx)\n", x, lshr32_3(x)); }
		if (lshr32_4(x) != x >> 4) { printf("mismatch: 0x%08lx >> 4 (got 0x%08lx)\n", x, lshr32_4(x)); }
		if (lshr32_5(x) != x >> 5) { printf("mismatch: 0x%08lx >> 5 (got 0x%08lx)\n", x, lshr32_5(x)); }
		if (lshr32_6(x) != x >> 6) { printf("mismatch: 0x%08lx >> 6 (got 0x%08lx)\n", x, lshr32_6(x)); }
		if (lshr32_7(x) != x >> 7) { printf("mismatch: 0x%08lx >> 7 (got 0x%08lx)\n", x, lshr32_7(x)); }
		if (lshr32_8(x) != x >> 8) { printf("mismatch: 0x%08lx >> 8 (got 0x%08lx)\n", x, lshr32_8(x)); }
		if (lshr32_9(x) != x >> 9) { printf("mismatch: 0x%08lx >> 9 (got 0x%08lx)\n", x, lshr32_9(x)); }
		if (lshr32_10(x) != x >> 10) { printf("mismatch: 0x%08lx >> 10 (got 0x%08lx)\n", x, lshr32_10(x)); }
		if (lshr32_11(x) != x >> 11) { printf("mismatch: 0x%08lx >> 11 (got 0x%08lx)\n", x, lshr32_11(x)); }
		if (lshr32_12(x) != x >> 12) { printf("mismatch: 0x%08lx >> 12 (got 0x%08lx)\n", x, lshr32_12(x)); }
		if (lshr32_13(x) != x >> 13) { printf("mismatch: 0x%08lx >> 13 (got 0x%08lx)\n", x, lshr32_13(x)); }
		if (lshr32_14(x) != x >> 14) { printf("mismatch: 0x%08lx >> 14 (got 0x%08lx)\n", x, lshr32_14(x)); }
		if (lshr32_15(x) != x >> 15) { printf("mismatch: 0x%08lx >> 15 (got 0x%08lx)\n", x, lshr32_15(x)); }
		if (lshr32_16(x) != x >> 16) { printf("mismatch: 0x%08lx >> 16 (got 0x%08lx)\n", x, lshr32_16(x)); }
		if (lshr32_17(x) != x >> 17) { printf("mismatch: 0x%08lx >> 17 (got 0x%08lx)\n", x, lshr32_17(x)); }
		if (lshr32_18(x) != x >> 18) { printf("mismatch: 0x%08lx >> 18 (got 0x%08lx)\n", x, lshr32_18(x)); }
		if (lshr32_19(x) != x >> 19) { printf("mismatch: 0x%08lx >> 19 (got 0x%08lx)\n", x, lshr32_19(x)); }
		if (lshr32_20(x) != x >> 20) { printf("mismatch: 0x%08lx >> 20 (got 0x%08lx)\n", x, lshr32_20(x)); }
		if (lshr32_21(x) != x >> 21) { printf("mismatch: 0x%08lx >> 21 (got 0x%08lx)\n", x, lshr32_21(x)); }
		if (lshr32_22(x) != x >> 22) { printf("mismatch: 0x%08lx >> 22 (got 0x%08lx)\n", x, lshr32_22(x)); }
		if (lshr32_23(x) != x >> 23) { printf("mismatch: 0x%08lx >> 23 (got 0x%08lx)\n", x, lshr32_23(x)); }
		if (lshr32_24(x) != x >> 24) { printf("mismatch: 0x%08lx >> 24 (got 0x%08lx)\n", x, lshr32_24(x)); }
		if (lshr32_25(x) != x >> 25) { printf("mismatch: 0x%08lx >> 25 (got 0x%08lx)\n", x, lshr32_25(x)); }
		if (lshr32_26(x) != x >> 26) { printf("mismatch: 0x%08lx >> 26 (got 0x%08lx)\n", x, lshr32_26(x)); }
		if (lshr32_27(x) != x >> 27) { printf("mismatch: 0x%08lx >> 27 (got 0x%08lx)\n", x, lshr32_27(x)); }
		if (lshr32_28(x) != x >> 28) { printf("mismatch: 0x%08lx >> 28 (got 0x%08lx)\n", x, lshr32_28(x)); }
		if (lshr32_29(x) != x >> 29) { printf("mismatch: 0x%08lx >> 29 (got 0x%08lx)\n", x, lshr32_29(x)); }
		if (lshr32_30(x) != x >> 30) { printf("mismatch: 0x%08lx >> 30 (got 0x%08lx)\n", x, lshr32_30(x)); }
		if (lshr32_31(x) != x >> 31) { printf("mismatch: 0x%08lx >> 31 (got 0x%08lx)\n", x, lshr32_31(x)); }

		if (ashr32_1(x) != (int32_t)x >> 1) { printf("mismatch: ashr32_1(%ld)\n", x); }
		if (ashr32_2(x) != (int32_t)x >> 2) { printf("mismatch: ashr32_2(%ld)\n", x); }
		if (ashr32_3(x) != (int32_t)x >> 3) { printf("mismatch: ashr32_3(%ld)\n", x); }
		if (ashr32_4(x) != (int32_t)x >> 4) { printf("mismatch: ashr32_4(%ld)\n", x); }
		if (ashr32_5(x) != (int32_t)x >> 5) { printf("mismatch: ashr32_5(%ld)\n", x); }
		if (ashr32_6(x) != (int32_t)x >> 6) { printf("mismatch: ashr32_6(%ld)\n", x); }
		if (ashr32_7(x) != (int32_t)x >> 7) { printf("mismatch: ashr32_7(%ld)\n", x); }
		if (ashr32_8(x) != (int32_t)x >> 8) { printf("mismatch: ashr32_8(%ld)\n", x); }
		if (ashr32_9(x) != (int32_t)x >> 9) { printf("mismatch: ashr32_9(%ld)\n", x); }
		if (ashr32_10(x) != (int32_t)x >> 10) { printf("mismatch: ashr32_10(%ld)\n", x); }
		if (ashr32_11(x) != (int32_t)x >> 11) { printf("mismatch: ashr32_11(%ld)\n", x); }
		if (ashr32_12(x) != (int32_t)x >> 12) { printf("mismatch: ashr32_12(%ld)\n", x); }
		if (ashr32_13(x) != (int32_t)x >> 13) { printf("mismatch: ashr32_13(%ld)\n", x); }
		if (ashr32_14(x) != (int32_t)x >> 14) { printf("mismatch: ashr32_14(%ld)\n", x); }
		if (ashr32_15(x) != (int32_t)x >> 15) { printf("mismatch: ashr32_15(%ld)\n", x); }
		if (ashr32_16(x) != (int32_t)x >> 16) { printf("mismatch: ashr32_16(%ld)\n", x); }
		if (ashr32_17(x) != (int32_t)x >> 17) { printf("mismatch: ashr32_17(%ld)\n", x); }
		if (ashr32_18(x) != (int32_t)x >> 18) { printf("mismatch: ashr32_18(%ld)\n", x); }
		if (ashr32_19(x) != (int32_t)x >> 19) { printf("mismatch: ashr32_19(%ld)\n", x); }
		if (ashr32_20(x) != (int32_t)x >> 20) { printf("mismatch: ashr32_20(%ld)\n", x); }
		if (ashr32_21(x) != (int32_t)x >> 21) { printf("mismatch: ashr32_21(%ld)\n", x); }
		if (ashr32_22(x) != (int32_t)x >> 22) { printf("mismatch: ashr32_22(%ld)\n", x); }
		if (ashr32_23(x) != (int32_t)x >> 23) { printf("mismatch: ashr32_23(%ld)\n", x); }
		if (ashr32_24(x) != (int32_t)x >> 24) { printf("mismatch: ashr32_24(%ld)\n", x); }
		if (ashr32_25(x) != (int32_t)x >> 25) { printf("mismatch: ashr32_25(%ld)\n", x); }
		if (ashr32_26(x) != (int32_t)x >> 26) { printf("mismatch: ashr32_26(%ld)\n", x); }
		if (ashr32_27(x) != (int32_t)x >> 27) { printf("mismatch: ashr32_27(%ld)\n", x); }
		if (ashr32_28(x) != (int32_t)x >> 28) { printf("mismatch: ashr32_28(%ld)\n", x); }
		if (ashr32_29(x) != (int32_t)x >> 29) { printf("mismatch: ashr32_29(%ld)\n", x); }
		if (ashr32_30(x) != (int32_t)x >> 30) { printf("mismatch: ashr32_30(%ld)\n", x); }
		if (ashr32_31(x) != (int32_t)x >> 31) { printf("mismatch: ashr32_31(%ld)\n", x); }
	}
	printf("done testing.\n");
	sleep_cpu();
	return 0;
}
