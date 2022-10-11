#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define TMin LONG_MIN
#define TMax LONG_MAX

#include "bits.h"
#include "btest.h"

test_rec test_set[] = {
//2
 {"copyLSB", (funct_t) copyLSB, (funct_t) test_copyLSB, 1,
    "! ~ & ^ | + << >>", 5, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"allOddBits", (funct_t) allOddBits, (funct_t) test_allOddBits, 1,
    "! ~ & ^ | + << >>", 14, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"isNotEqual", (funct_t) isNotEqual, (funct_t) test_isNotEqual, 2,
    "! ~ & ^ | + << >>", 6, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dividePower2", (funct_t) dividePower2, (funct_t) test_dividePower2, 2,
    "! ~ & ^ | + << >>", 15, 2,
  {{TMin, TMax},{0,62},{TMin,TMax}}},
//3
 {"remainderPower2", (funct_t) remainderPower2, (funct_t) test_remainderPower2, 2,
    "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{0,30},{TMin,TMax}}},
 {"rotateLeft", (funct_t) rotateLeft, (funct_t) test_rotateLeft,
   2, "! ~ & ^ | + << >>", 25, 3,
  {{TMin, TMax},{0,63},{TMin,TMax}}},
 {"bitMask", (funct_t) bitMask, (funct_t) test_bitMask, 2,
    "! ~ & ^ | + << >>", 16, 3,
  {{0, 63},{0,63},{TMin,TMax}}},
 {"isPower2", (funct_t) isPower2, (funct_t) test_isPower2, 1, "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//4
 {"allAsciiDigits", (funct_t) allAsciiDigits, (funct_t) test_allAsciiDigits, 1,
    "! ~ & ^ | << >>", 30, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"trueThreeFourths", (funct_t) trueThreeFourths, (funct_t) test_trueThreeFourths, 1,
    "! ~ & ^ | + << >>", 20, 4,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
 {"bitCount", (funct_t) bitCount, (funct_t) test_bitCount, 1, "! ~ & ^ | + << >>", 50, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
{
    "", NULL, NULL, 0, "", 0, 0, {
        {0, 0}, {0, 0}, {
            0, 0
        }
    }
}
}
;
