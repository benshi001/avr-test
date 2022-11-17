//===------------- divmodsi4.S - sint32 div & mod -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// __divmodsi4 has a special ABI as described in gcc/config/avr/avr.md: the two
// parameters are passed as usual (in r22-r25 and r18-r21). The quotient is
// returned in r18-r21 and the remainder is returned in r22-r25. Only r26, r27,
// r30, r31, CC and Rtmp may be clobbered.
//
//===----------------------------------------------------------------------===//

  .text
  .align 2

#if !defined(__AVR_TINY__) // TODO: add support for avrtiny

  .globl test_divmodsi4
  .type  test_divmodsi4, @function

; parameter num is stored in r22-r25
; parameter den is stored in r18-r21
; quotient is stored in r22-r25
; remainder is stored in r18-r21
; temporary registers are r26, r27, r30, r31, rtmp.
test_divmodsi4:

  ; - set bit 7 to the sign of (num ^ den)
  ; - set bit 6 to the sign of num
  mov r31, r25
  eor r31, r21
  bst r25, 7
  bld r31, 6

  ; negate num:
  ; if (num < 0)
  ;   num = -num;
  sbrs r25, 7
  rjmp 1f
  com r25
  com r24
  com r23
  neg r22
  sbci r23, -1
  sbci r24, -1
  sbci r25, -1
1:

  ; negate den:
  ; if (den < 0)
  ;   den = -den;
  sbrs r21, 7
  rjmp 2f
  com r21
  com r20
  com r19
  neg r18
  sbci r19, -1
  sbci r20, -1
  sbci r21, -1
2:

  ; Note: r31 is preserved by test_udivmodsi4.
#if defined(__AVR_HAVE_JMP_CALL__)
  call test_udivmodsi4
#else
  rcall test_udivmodsi4
#endif

  ; negate quotient:
  ; if ((original num < 0) != (original den < 0))
  ;   quo = -quo;
  sbrs r31, 7
  rjmp 3f
  com r21
  com r20
  com r19
  neg r18
  sbci r19, -1
  sbci r20, -1
  sbci r21, -1
3:

  ; negate remainder
  ; if (original num < 0)
  ;   rem = -rem;
  sbrs r31, 6
  rjmp 4f
  com r25
  com r24
  com r23
  neg r22
  sbci r23, -1
  sbci r24, -1
  sbci r25, -1
4:

  ret

#endif // defined(__AVR_TINY__)
