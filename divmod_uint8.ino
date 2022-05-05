// Copyright 2022 Ben Shi. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// This program tests my software uint8 division function udivmodqi4
// against libgcc's implementation.

// LLVM Differential Revision: https://reviews.llvm.org/D124600

__attribute__((naked)) unsigned int udivmodqi4(unsigned char a, unsigned char b) { 
  __asm__ __volatile__ (
      "\tsub     r25, r25           ; Initialize the remainder to zero.\n"
      "\tldi     r23, 9             ; Only loop 8 rounds for uint8.\n"
      "\n"
      "udivmodqi4_loop:\n"
      "\tadc     r24, r24\n"
      "\tdec     r23\n"
      "\tbreq    udivmodqi4_end\n"
      "\tadc     r25, r25\n"
      "\tcp      r25, r22           ; Compare with the divisor.\n"
      "\tbrcs    udivmodqi4_loop\n"
      "\tsub     r25, r22           ; Subtract the divisor.\n"
      "\trjmp    udivmodqi4_loop\n"
      "\n"
      "udivmodqi4_end:\n"
      "\tcom     r24                ; The uint8 quotient is returned via R24.\n"
      "\tret                        ; The uint8 remainder is returned via R25.");
}

volatile unsigned char arr0[] = {47, 175, 85, 138, 116, 4, 126, 109, 137, 40, 92, 173, 11, 196, 163, 103, 67, 66, 74, 8, 30, 59, 26, 120, 197, 231, 70, 1, 23, 158, 188, 197, 79, 145, 80, 67, 21, 78, 48, 159, 118, 141, 204, 1, 82, 112, 104, 21, 51, 50, 29, 208, 109, 182, 73, 179, 158, 144, 180, 53, 174, 240, 122, 125, 2, 202, 193, 23, 26, 241, 182, 144, 254, 131, 146, 81, 116, 122, 230, 167, 45, 4, 120, 26, 187, 66, 205, 217, 82, 130, 143, 1, 242, 10, 254, 244, 213, 192, 13, 111, 50, 67, 127, 50, 71, 145, 3, 187, 140, 233, 99, 185, 110, 91, 211, 42, 29, 162, 131, 111, 164, 19, 113, 152, 30, 112, 13, 115, 176, 26, 98, 98, 94, 225, 20, 165, 243, 24, 224, 128, 129, 195, 58, 239, 158, 141, 153, 188, 175, 157, 44, 85, 176, 29, 109, 78, 13, 122, 65, 189, 21, 163, 160, 242, 6, 180, 24, 249, 76, 120, 122, 206, 60, 52, 62, 218, 193, 88, 151, 114, 245, 196, 71, 38, 225, 52, 117, 239, 46, 182, 45, 67, 218, 205, 181, 224, 3, 77, 218, 79, 197, 212, 157, 2, 9, 220, 93, 74, 180, 244, 60, 170, 57, 131, 208, 28, 183, 197, 139, 102, 252, 56, 169, 215, 134, 223, 184, 137, 172, 19, 216, 115, 231, 246, 244, 112, 83, 82, 186, 8, 72, 247, 50, 1, 250, 130, 29, 51, 73, 40, 153, 70, 97, 194, 157, 231, 34, 86, 240, 207, 105, 201, 67, 208, 64, 183, 65, 147, 11, 123, 155, 210, 242, 77, 211, 238, 208, 113, 161, 26, 153, 59, 223, 122, 125, 125, 225, 160, 83, 210, 112, 60, 29, 51, 13, 93, 234, 205, 241, 117, 73, 13, 72, 61, 91, 156, 171, 44, 14, 77, 197, 39, 8, 165, 34, 133, 35, 4, 38, 118, 215, 22, 178, 244, 73, 63, 209, 180, 13, 67, 42, 213, 81, 115, 146, 44, 143, 62, 215, 157, 11, 157, 68, 19, 67, 102, 25, 229, 107, 63, 219, 194, 86, 14, 55, 31, 204, 136, 211, 217, 204, 254, 47, 157, 241, 194, 201, 129, 128, 161, 158, 12, 190, 226, 31, 129, 201, 56, 103, 180, 247, 194, 119, 205, 208, 46, 236, 29, 182, 193, 246, 131, 192, 165, 33, 50, 231, 106, 179, 105, 12, 82, 117, 74, 180, 20, 203, 126, 204, 51, 51, 196, 117, 42, 146, 197, 88, 127, 226, 16, 192, 89, 19, 1, 0, 180, 51, 231, 31, 230, 208, 171, 184, 197, 245, 110, 218, 194, 236, 167, 117, 160, 235, 235, 202, 253, 177, 36, 252, 21, 179, 190, 110, 70, 191, 110, 250, 243, 214, 27, 90, 39, 70, 20, 237, 60, 130, 200, 126, 238, 239, 244, 143, 91, 96, 218, 89, 145, 254, 86, 166, 50, 148, 149, 120, 212, 131, 243, 200, 90, 142, 162, 2, 212, 182, 239, 144, 184, 56, 16, 168, 167, 132, 183, 3, 228, 146, 219, 245, 17, 177, 29, 67, 71, 178, 60, 28, 54, 175, 100, 17, 62, 7, 19, 146, 190, 3, 35, 246, 186, 51, 159, 98, 55, 215, 101, 28, 233, 192, 146, 251, 114, 175, 190, 185, 98, 122, 85, 24, 42, 185, 168, 231, 65, 187, 122, 127, 62, 158, 118, 248, 81, 150, 91, 137, 237, 64, 37, 215, 1, 183, 211, 116, 230, 19, 173, 200, 141, 131, 97, 184, 188, 10, 160, 253, 70, 28, 125, 132, 58, 116, 253, 139, 11, 89, 148, 248, 26, 58, 80};
volatile unsigned char arr1[] = {13, 2, 8, 1, 15, 12, 2, 12, 10, 13, 4, 14, 6, 15, 2, 5, 10, 7, 2, 7, 12, 13, 12, 8, 1, 4, 7, 1, 15, 5, 7, 4, 13, 6, 12, 4, 9, 13, 1, 3, 10, 4, 2, 15, 3, 10, 11, 4, 8, 5, 3, 4, 2, 14, 11, 10, 2, 2, 2, 1, 13, 15, 12, 11, 5, 8, 14, 13, 5, 6, 1, 6, 10, 9, 5, 12, 10, 8, 1, 2, 12, 10, 5, 5, 8, 15, 6, 10, 9, 8, 2, 6, 7, 13, 8, 12, 5, 14, 1, 1, 4, 8, 6, 13, 1, 3, 2, 2, 10, 9, 3, 6, 3, 14, 2, 2, 14, 8, 11, 14, 15, 5, 11, 13, 2, 4, 9, 14, 9, 2, 6, 12, 9, 12, 2, 2, 14, 10, 3, 15, 3, 13, 12, 12, 11, 13, 13, 1, 5, 1, 6, 4, 5, 2, 9, 6, 5, 9, 11, 5, 10, 2, 1, 11, 5, 9, 12, 3, 3, 6, 9, 12, 10, 5, 8, 13, 2, 13, 13, 14, 13, 4, 9, 2, 12, 2, 14, 1, 11, 2, 5, 5, 3, 12, 7, 7, 13, 10, 1, 15, 1, 1, 4, 2, 5, 3, 14, 13, 15, 4, 11, 4, 14, 5, 12, 10, 6, 11, 2, 8, 4, 13, 13, 6, 9, 4, 4, 13, 6, 11, 13, 13, 11, 1, 14, 7, 3, 5, 4, 10, 8, 15, 13, 6, 11, 10, 7, 8, 12, 8, 1, 15, 5, 5, 12, 5, 15, 7, 3, 5, 2, 7, 2, 4, 14, 1, 10, 8, 5, 13, 2, 4, 4, 7, 9, 6, 8, 15, 14, 4, 14, 14, 3, 3, 3, 6, 14, 2, 12, 8, 7, 5, 14, 8, 8, 12, 15, 2, 12, 4, 6, 5, 7, 2, 11, 7, 7, 3, 13, 5, 13, 3, 10, 7, 5, 12, 12, 11, 6, 8, 3, 12, 12, 2, 11, 11, 5, 11, 4, 8, 6, 2, 13, 5, 3, 15, 3, 1, 10, 1, 6, 7, 3, 7, 14, 15, 4, 2, 2, 1, 2, 4, 12, 5, 12, 14, 1, 9, 1, 4, 1, 7, 5, 5, 11, 14, 5, 5, 15, 14, 5, 12, 5, 15, 3, 10, 6, 13, 12, 14, 13, 13, 2, 1, 2, 6, 15, 9, 14, 15, 13, 6, 13, 9, 11, 15, 15, 15, 5, 14, 5, 1, 2, 9, 7, 4, 11, 4, 9, 7, 2, 6, 11, 4, 14, 4, 1, 13, 13, 14, 4, 2, 11, 2, 2, 6, 8, 1, 12, 12, 6, 1, 13, 7, 2, 11, 3, 12, 15, 11, 10, 1, 8, 5, 11, 6, 15, 11, 10, 4, 1, 6, 5, 12, 7, 14, 9, 14, 14, 6, 3, 12, 13, 7, 3, 14, 2, 12, 2, 8, 14, 11, 9, 7, 7, 4, 4, 14, 15, 6, 2, 7, 11, 14, 3, 2, 12, 4, 7, 2, 1, 1, 13, 13, 14, 8, 4, 1, 11, 12, 8, 10, 15, 8, 8, 6, 12, 11, 11, 3, 1, 13, 1, 3, 11, 4, 11, 7, 14, 3, 15, 14, 10, 13, 3, 9, 12, 13, 1, 7, 10, 15, 1, 9, 8, 15, 6, 11, 11, 2, 5, 3, 6, 5, 6, 1, 15, 1, 14, 13, 10, 13, 3, 12, 2, 6, 5, 13, 3, 12, 12, 4, 11, 4, 12, 10, 4, 10, 5, 14, 11, 9, 8, 1, 6, 5, 8, 5, 13, 6, 3, 14, 10, 12, 10, 4, 2, 6, 1, 12, 2, 4, 7, 5, 8, 4, 14, 11, 5, 11};

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(115200);         // Initialize the communication port.
}

void loop(void) {
  unsigned i;
  for (i = 0; i < sizeof(arr0) / sizeof(*arr0); i++) {
    // Test uint8 div.
    volatile unsigned char i0 = arr0[i] / arr1[i];
    volatile unsigned char i1 = udivmodqi4(arr0[i], arr1[i]);
    Serial.println(i0 == i1 ? "uint8 div correct" : "uint8 div incorrect");

    // Test uint8 mod.
    volatile unsigned char j0 = arr0[i] % arr1[i];
    volatile unsigned char j1 = udivmodqi4(arr0[i], arr1[i]) >> 8;
    Serial.println(j0 == j1 ? "uint8 mod correct" : "uint8 mod incorrect");

    delay(100);
  }
}
