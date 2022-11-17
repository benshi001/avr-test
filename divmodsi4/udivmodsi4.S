//===------------ udivmodsi4.S - uint32 div & mod -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The code below corresponds to the following C code, that is tested with over
// 100000000000 (1e11 or over 2^36) random combinations of numerator and
// denominator.
//
//   uint64_t udivmodsi4(uint32_t num, uint32_t den) {
//       uint64_t n = num;
//       for (char i = 32; i != 0; i--) {
//           n <<= 1;
//           if ((uint32_t)(n>>32) >= den) {
//               // This bit of the quotient is one.
//               n |= 1;
//               // The next line is complicated in C, but simple in assembly.
//               // It subtracts den from the upper 32 bits of n.
//               n = (n & 0xffffffff) | ((uint64_t)((uint32_t)(n >> 32) - den) << 32);
//           }
//       }
//       // Quotient is stored in the lower 32 bits, remainder is stored in the
//       // upper 32 bits.
//       return n;
//   }
//
// This is essentially binary long division. The value n actually contains two
// different values at once, to reduce the number of registers necessary. At the
// start, it contains just the numerator which is shifted left by one each
// iteration. The bottom bits are the quotient bits. Each iteration one bit of
// the quotient is calculated. The denominator is subtracted each iteration from
// a part of the numerator, so that at the end of the loop the numerator becomes
// the remainder.
//
// __udivmodsi4 has a special ABI as described in gcc/config/avr/avr.md: the two
// parameters are passed as usual (in r22-r25 and r18-r21). The quotient is
// returned in r18-r21 and the remainder is returned in r22-r25. Only r26, r27,
// r30, r31, CC and Rtmp may be clobbered.
//
//===----------------------------------------------------------------------===//

  .text
  .align 2

#if !defined(__AVR_TINY__) // TODO: add support for avrtiny

  .set __tmp_reg__, 0
  .set __zero_reg__, 1

  .globl test_udivmodsi4
  .type  test_udivmodsi4, @function

; parameter num is stored in r22-r25
; parameter den is stored in r18-r21
; quotient is stored in r22-r25
; remainder is stored in r18-r21
; temporary registers are r26, r27, r30, r31, rtmp.
; However, test_divmodsi4 expects r31 to be preserved so it can't be used here.
test_udivmodsi4:
  ; n is stored in in r22-r25, r26, r27, __tmp_reg__, __zero_reg__
  ; clear the upper 32 bits of n
  clr r26
  clr r27
  clr __tmp_reg__
  ;clr __zero_reg__ ; not needed (already zero)

  ; char i = 32
  ldi r30, 32

1:
  ; n <<= 1
  lsl r22
  rol r23
  rol r24
  rol r25
  rol r26
  rol r27
  rol __tmp_reg__
  rol __zero_reg__

  ; if ((uint32_t)(n>>32) >= den)
  cp  r26,          r18
  cpc r27,          r19
  cpc __tmp_reg__,  r20
  cpc __zero_reg__, r21
  brlo 2f

  ; n |= 1
  ori r22, 1

  ; n = (n & 0xffffffff) | ((uint64_t)((uint32_t)(n >> 32) - den) << 32);
  ; (in other words: subtract den from the upper bits of n)
  sub r26,          r18
  sbc r27,          r19
  sbc __tmp_reg__,  r20
  sbc __zero_reg__, r21

2:
  ; i--
  dec r30
  ; if (i == 0) goto start of loop
  brne 1b

  ; move quotient (lower bits of n) to output registers r18-r21
  mov r18, r22
  mov r19, r23
  mov r20, r24
  mov r21, r25

  ; move remainder (upper bits of n) to output registers r22-r25
  mov r22, r26
  mov r23, r27
  mov r24, __tmp_reg__
  mov r25, __zero_reg__

  ; clear zero register after use
  clr __zero_reg__

  ret

#endif // defined(__AVR_TINY__)
