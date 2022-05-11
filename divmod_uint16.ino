// Copyright 2022 Ben Shi. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// This program tests my software uint16 division function udivmodhi4
// against libgcc's implementation.

// LLVM Differential Revision: https://reviews.llvm.org/D124600

__attribute__((naked)) unsigned long udivmodhi4(unsigned int a, unsigned int b) { 
  __asm__ __volatile__ (
      "\tsub     r26, r26\n"
      "\tsub     r27, r27           ; Initialize the remainder to zero.\n"
      "\tldi     r21, 17            ; Only loop 16 cycles for uint16.\n"
      "\n"
      "udivmodhi4_loop:\n"
      "\tadc     r24, r24\n"
      "\tadc     r25, r25\n"
      "\tdec     r21\n"
      "\tbreq    udivmodhi4_end\n"
      "\tadc     r26, r26\n"
      "\tadc     r27, r27\n"
      "\tcp      r26, r22\n"
      "\tcpc     r27, r23           ; Compare with the divisor.\n"
      "\tbrcs    udivmodhi4_loop\n"
      "\tsub     r26, r22\n"
      "\tsbc     r27, r23           ; Subtract the divisor.\n"
      "\trjmp    udivmodhi4_loop\n"
      "\n"
      "udivmodhi4_end:\n"
      "\tcom     r24\n"
      "\tcom     r25\n"
      "\tmov     r22, r24\n"
      "\tmov     r23, r25           ; The quotient is returned in R23:R22.\n"
      "\tmov     r24, r26\n"
      "\tmov     r25, r27           ; The remainder is returned in in R25:R24.\n"
      "\tret");
}

volatile unsigned int arr0[] = {913, 52015, 48654, 35307, 7122, 25448, 30970, 33493, 45253, 7382, 19198, 49018, 65100, 22408, 65419, 39997, 45823, 10373, 34214, 36502, 47076, 29985, 51417, 19881, 1623, 11299, 34238, 55467, 63009, 3689, 63179, 63922, 55705, 13530, 33694, 30059, 38978, 31896, 63552, 18697, 39279, 17215, 2180, 38844, 39623, 34831, 46073, 52678, 12436, 14752, 56412, 59512, 11969, 42295, 13858, 46360, 53594, 15329, 3524, 18300, 19018, 1169, 16687, 41955, 14699, 17613, 6479, 53678, 49509, 4496, 39607, 56020, 54478, 9019, 62096, 61333, 43851, 42634, 48477, 23519, 24619, 39354, 50264, 36588, 48881, 64122, 50180, 4172, 46683, 53705, 22472, 167, 22106, 6391, 42122, 4037, 56771, 15834, 24947, 7978, 20330, 64554, 63998, 9274, 8039, 60560, 5072, 19122, 37659, 20781, 42641, 62278, 27368, 27370, 564, 43481, 58725, 50744, 47654, 39873, 6146, 37358, 40040, 61019, 43750, 49395, 65057, 2218, 65229, 24469, 10196, 52791, 23489, 8660, 29297, 64295, 36452, 1602, 17882, 41343, 22383, 60523, 5319, 16983, 55126, 5883, 60465, 48316, 23859, 42584, 55421, 62773, 14407, 29927, 58257, 25389, 46554, 57779, 60375, 13480, 16714, 5036, 736, 7435, 46463, 30034, 6195, 17380, 64403, 56844, 58724, 21251, 19064, 64043, 38235, 8655, 37158, 33165, 24203, 28249, 42981, 14090, 25487, 24620, 44017, 18210, 17242, 57803, 43221, 12082, 5748, 27167, 49885, 39251, 34602, 30814, 36517, 8029, 15426, 35385, 64873, 8615, 56637, 18403, 39890, 62104, 59825, 44280, 62501, 18494, 6995, 7179, 32584, 32482, 31799, 43833, 17924, 16273, 36101, 28378, 28355, 9081, 55545, 12706, 48332, 57380, 10752, 52082, 65409, 26178, 21932, 31980, 2026, 45801, 17615, 9148, 42370, 44672, 53429, 6568, 63166, 60424, 13747, 30215, 60138, 12779, 41280, 45295, 29052, 11846, 8138, 24640, 53694, 63683, 37346, 3724, 55528, 15330, 55806, 22635, 8740, 44970, 21847, 10766, 25237, 39462, 52682, 34839, 18599, 40576, 41408, 48998, 2697, 22387, 46445, 62835, 35166, 22191, 42595, 64219, 1269, 50733, 23324, 54964, 16114, 27902, 25920, 38874, 10464, 16191, 61509, 19204, 61161, 50588, 62738, 53630, 57282, 49885, 22935, 10347};
volatile unsigned int arr1[] = {3123, 3690, 597, 1800, 2467, 377, 450, 4011, 758, 1953, 3932, 318, 703, 3968, 674, 2477, 3805, 2054, 2959, 446, 3185, 2443, 4020, 3513, 2234, 270, 774, 1571, 1915, 1141, 2610, 815, 736, 3207, 2615, 3075, 3585, 2938, 2991, 120, 796, 2828, 438, 1499, 2701, 1112, 3849, 2283, 3166, 2713, 2729, 2128, 933, 2527, 1547, 3167, 2797, 2193, 644, 490, 3334, 3254, 1305, 4070, 2239, 3921, 3050, 1729, 2764, 1819, 1849, 3432, 552, 2160, 708, 3126, 3144, 334, 1314, 2216, 3047, 4044, 121, 3853, 2348, 1668, 2797, 1050, 3733, 3313, 1412, 2972, 2345, 2718, 2819, 489, 2416, 1647, 2090, 1085, 3466, 3811, 294, 4018, 1876, 1002, 3049, 798, 1337, 141, 3014, 161, 4057, 3135, 3886, 2310, 581, 2589, 3360, 91, 1679, 678, 3064, 4024, 3268, 1788, 290, 1589, 3307, 2252, 2546, 2678, 1969, 2840, 2474, 3717, 3842, 1428, 420, 956, 1441, 3306, 1118, 1403, 2219, 909, 3713, 2672, 3370, 2851, 2763, 955, 3401, 1604, 756, 2574, 3265, 919, 4035, 2477, 3171, 2486, 1061, 917, 1231, 3535, 412, 850, 740, 704, 1807, 2182, 3883, 2925, 3457, 1879, 3706, 3076, 456, 2982, 1704, 3091, 3809, 1010, 601, 470, 3456, 3866, 1261, 3396, 2248, 338, 1787, 3309, 1127, 2890, 2621, 1411, 3612, 3234, 1988, 1324, 1321, 1776, 26, 555, 3655, 3605, 3631, 3983, 2492, 1240, 2979, 2206, 2122, 3580, 2548, 1483, 3351, 3810, 784, 1377, 4020, 2443, 463, 924, 1238, 3085, 2336, 628, 2224, 229, 1952, 3417, 1877, 1851, 3972, 1437, 1361, 3381, 1197, 3725, 398, 81, 1836, 2521, 3662, 161, 3876, 2790, 3971, 566, 72, 3768, 2881, 536, 598, 3992, 3493, 2806, 525, 1622, 3035, 2349, 816, 817, 105, 565, 2126, 1338, 3946, 3323, 968, 122, 3404, 2676, 2643, 2843, 2710, 2296, 1539, 2458, 2862, 1483, 2132, 1649, 1891, 2602, 1418, 1289, 1313, 1943, 2911, 253, 197, 3599, 942, 175, 70, 2940};

void setup(void) {
  Serial.begin(115200);         // Initialize the communication port.
}

void loop(void) {
  unsigned int i;
  for (i = 0; i < sizeof(arr0) / sizeof(*arr0); i++) {
    // Test uint16 div.
    volatile unsigned int i0 = arr0[i] / arr1[i];
    volatile unsigned int i1 = (unsigned int) udivmodhi4(arr0[i], arr1[i]);
    if (i0 == i1)
      Serial.println("uint16 div correct");
    else
      Serial.println("uint16 div incorrect");

    // Test uint16 mod.
    volatile unsigned int j0 = arr0[i] % arr1[i];
    volatile unsigned int j1 = (unsigned int) (udivmodhi4(arr0[i], arr1[i]) >> 16);
    if (j0 == j1)
      Serial.println("uint16 mod correct");
    else
      Serial.println("uint16 mod incorrect");

    delay(100);
  }
}
