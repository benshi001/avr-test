// Copyright 2022 Ben Shi. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// This program tests the software int8 multiplication function `__mulqi3`
// against AVR's hardware multiplier.

// LLVM Differential Revision: https://reviews.llvm.org/D125077

__attribute__((naked)) char mulqi3(char a, char b) {
  __asm__ __volatile__ (
      "\teor   r0, r0          ; S = 0;\n"
      "\n"
      "__mulqi3_loop:\n"
      "\tcpi   r24, 0\n"
      "\tbreq  __mulqi3_end    ; while (A != 0) {\n"
      "\tsbrc  r24, 0          ;   if (A & 1)\n"
      "\tadd   r0, r22         ;     S += B;\n"
      "\tadd   r22, r22        ;   B <<= 1;\n"
      "\tlsr   r24             ;   A = ((unsigned char) A) >> 1;\n"
      "\trjmp  __mulqi3_loop   ; }\n"
      "\n"
      "__mulqi3_end:\n"
      "\tmov   r24, r0\n"
      "\tret                   ; return S;\n");
}

volatile int arr0[] = {17767, 9158, -26519, 18547, -9135, 23807, -27574, 22764, 7977, 31949, 22714, -10325, 16882, 7931, -22045, -7866, 124, 25282, 2132, 10232, 8987, -5656, -12825, 17293, 3958, 9562, -1746, 29283, -15821, -10337, -15159, 1946, -1178, 23858, 20493, -10313, -17871, -7080, 12451, -9894, 24869, -30371, -20219, -23785, -22440, 23273, -31650, -22316, -16981, -29518, -12083, -7994, 30363, -24908, 9300, -31215, -15346, 7554, -1932, -31167, -2783, -17091, -29220, -3961, 6768, -8727, -14274, -11103, -15807, -1823, -20996, 9063, -32194, 24321, -14722, 10903, -17942, 19164, -11413, 30614, -10353, -23496, 22620, 20010, 17132, 31920, -11205, 1787, -26062, -13137, -29380, -28844, -30228, 6936, 32731, -23460, -1790, 18458, 30974, -17597, 16635, 9978, -8534, -15558, -31237, -23255, -4655, 16358, -4091, -16068, -18564, -14444, 25973, 4056, 5566, -22431, -29559, -5639, -20644, 9915, -18776, 15513, -18929, 16533, 22449, 13803, -6927, 20659, 32261, 24047, 3063, -16640, -31511, -5471, -32198, 2789, -28726, 28683, 19147, 32720, 12616, 583, 18276, -26947, 4639, 23843, 16158, -24920, 18204, -4485, -15004, -571, 11028, 31603, 15962, -32059, -20130, 9035, -11399, 12131, -32453, -8336, -4508, 1572, -13807, 28830, 4361, 23004, -8022, 23508, -9812, 4594, 24091, 8464, -22353, 28731, 32307, -6195, 3811, -15024, -10680, -11193, -15595, 348, 20411, 367, -31710, 281, 9402, 22427, 12413, -23051, 14091, 7905, -21478, 284, -28801, -17117, 23288, 28713, 6392, 13476, -32229, 30483, 21941, 10954, -6322, -11288, 4760, -2510, -26312, -5920, -13703, 23629, -5571, 6708, 23996, 28255, 6990, -32137, -14854, 19403, 10348, -763, 27308, -11130, -479, -1493, -28246, 22810, 27221, -21854, -29250, -5008, 8629, -7309, 5947, 2308, -18596, 10707, -202, 20628, 4787, -13905, -21278, -784, -7196, 2718, 27471, -206, -29419, 12617, 19197, -19070, 11854, -19031, -30200, 11376, -20524, 7090, -31350, 6697, -14764, 4936, 1690, -6134, -2372, 7637, -3826, -20968, 18344, -4028, -340, 23131, -17933, -21618, 22348, -25129, -18899, -15717, -25335, 17218, -3099, -6138, -1852, 8755, -25169, -32051, 20131, 19844, -24961, -11219, 26541, 25812, -6282, 28231, 19678, -8654, -29668, 15852, };
volatile int arr1[] = {-29622, -11324, 11824, -29962, 11808, -6109, 13957, -31380, -31237, -4942, 18439, 8964, 12276, 15340, 2827, 10425, 24096, -22342, -21626, -21309, -2498, 18949, -32527, 24044, -20775, 26727, -13261, -1097, 18073, 22608, 14755, -11549, 11284, 26579, 24025, 23092, 20471, -27554, -8288, -10766, -32496, 10152, -1802, -20219, 25492, 1025, -9794, -15948, -21316, -31420, 28280, -23814, -12471, -4247, 230, 32291, 22480, -13030, 31194, -24983, 9578, -19586, 29004, 20862, 6993, -12507, -21581, 27464, 25476, -29869, 16698, -7020, -19717, 14897, -27239, 5776, 15922, 28503, -10172, -5394, -2917, 18108, -29207, -15387, 13861, -28977, 16904, -29195, 23529, -17438, 11358, -32429, 28512, -25174, -11566, -30030, 27856, 32389, -2566, -12204, 2520, 14133, -19224, -17196, 29030, 19074, -11420, -20584, -17959, -21592, -25977, -20875, -3483, 10352, 29274, 10378, -18625, -19358, -18816, 4905, 28740, -7458, -27524, -8283, -32631, 26446, 27223, -4775, -6701, 24657, -16979, -4180, -26746, 29333, -21376, 2284, -17129, 32740, -18299, 30449, 11148, 21260, 9574, 7665, 31612, -26688, 18044, 12987, 19490, -772, 17892, -17306, -8230, -9631, -25589, 24675, 16815, 1634, 19900, 10115, 26292, 2921, 5935, -454, 32255, -15441, 1831, 15126, 17299, -16468, -19961, 28447, 4792, -10387, -29423, -29132, 28461, -11379, -16145, -17585, -12151, 1748, 30646, -20381, -7883, 5057, 4295, 8932, 6692, 24195, 19047, -32552, 27117, 24982, 32530, -6164, 9541, -31175, 8962, 26840, 17893, -10998, -10248, 22685, -21385, 25865, -6447, 7077, 14486, -22591, -10508, 2335, -20843, 20138, -18046, -28726, 25196, -13751, -19794, 31888, 10445, -746, -664, -27974, 24236, 31866, 31398, -31758, 692, -25176, -4918, 18585, 29362, -15166, -24265, 7978, 10699, -30712, 15055, 25185, 12233, 4547, 27520, -8610, 24686, 9475, 28200, -15654, -4276, 8407, 16234, 6169, 7661, 15570, -21805, 31897, -18100, 9593, 139, -17408, -15582, -4778, 1178, 13780, -19944, -23087, 21758, -9244, 11737, -28723, 15941, 23971, -24175, -22074, 15361, 511, -12599, -21974, -15143, -16875, -13567, 1091, -10705, -5906, 16661, -32510, 25991, -1439, -22916, 26131, -18846, 27038, 21353, -17668, -24718, 1409, 24781, -2959, -7835, -29018, };

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(115200);         // Initialize the communication port.
}

void loop(void) {
  // put your main code here, to run repeatedly:
  unsigned int i = 0;
  for (i = 0; i < sizeof(arr0) / sizeof(*arr0); i++) {
    // Check int8 mul.
    volatile char c0 = arr0[i];
    volatile char c1 = arr1[i];
    volatile char cc0 = c0 * c1;
    volatile char cc1 = mulqi3(c0, c1);
    Serial.println(cc0 == cc1 ? "int8 mul correct" : "int8 mul incorrect");
    delay(100);
  }
}
