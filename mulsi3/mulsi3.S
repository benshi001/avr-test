//===------------ mulsi3.S - int32 multiplication -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The assembly implementation corresponds to the following C code, that is
// tested with over 10000000000 (1e10) random combinations of A and B:
//
//   uint32_t test_mulsi3(uint32_t A, uint32_t B) {
//     uint32_t S = 0;
//     do {
//       if (A & 1)
//         S += B;
//       A >>= 1;
//       B <<= 1;
//     } while (A != 0);
//     return S;
//   }
//
// __mulsi3 has a special ABI: the calling convention is as usual except that
// only R26, R27, Rtmp and SREG are clobbered.
//
//===----------------------------------------------------------------------===//

    .text
    .align 2

#if !defined(__AVR_TINY__) // TODO: add support for avrtiny

    .set __tmp_reg__, 0
    .set __zero_reg__, 1

    .globl test_mulsi3
    .type  test_mulsi3, @function

; parameter A is stored in r22-r25
; parameter B is stored in r18-r21
; result is stored in r22-r25
test_mulsi3:
    ; S = 0;
    clr   r26
    clr   r27
    clr   __tmp_reg__
    ;clr   __zero_reg__ ; not needed (already zero)

1: ; loop
    ; if (A & 1)
    ;   S += B;
    sbrs r22, 0
    rjmp 2f
    add r26,          r18
    adc r27,          r19
    adc __tmp_reg__,  r20
    adc __zero_reg__, r21

2:
    ; A >>= 1;
    lsr r25
    ror r24
    ror r23
    ror r22

    ; B <<= 1;
    lsl r18
    rol r19
    rol r20
    rol r21

    ; do { ... } while (A != 0);
    subi r22, 0
    sbci r23, 0
    sbci r24, 0
    sbci r25, 0
    brne 1b

3:
    ; Return the result via r22-r25.
    mov   r22, r26
    mov   r23, r27
    mov   r24, __tmp_reg__
    mov   r25, __zero_reg__
    ; Restore __zero_reg__ to 0.
    clr   __zero_reg__
    ; Return to parent.
    ret

#endif // defined(__AVR_TINY__)
