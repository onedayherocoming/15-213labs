/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
    union {
        unsigned u;
        float f;
    } a;
    a.u = u;
    return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
    union {
        unsigned u;
        float f;
    } a;
    a.f = f;
    return a.u;
}
//2
long test_copyLSB(long x)
{
  return (x & 0x1L) ? -1 : 0;
}
long test_allOddBits(long x) {
  int i;
  for (i = 1; i < 64; i+=2)
      if ((x & (1L<<i)) == 0)
          return 0L;
  return 1L;
}
long test_isNotEqual(long x, long y)
{
  return (long) (x != y);
}
long test_dividePower2(long x, long n)
{
    long p2n = 1L<<n;
    return x/p2n;
}
//3
long test_remainderPower2(long x, long n)
{
    long p2n = 1L<<n;
    return x%p2n;
}
long test_rotateLeft(long x, long n) {
  unsigned long u = (unsigned long) x;
  long i;
  for (i = 0; i < n; i++) {
      unsigned long msb = u >> 63;
      unsigned long rest = u << 1;
      u = rest | msb;
  }
  return (long) u;
}
long test_bitMask(long highbit, long lowbit)
{
  long result = 0L;
  int i;
  for (i = lowbit; i <= highbit; i++)
    result |= 1L << i;
  return result;
}
long test_isPower2(long x) {
  long i;
  for (i = 0; i < 63; i++) {
    if (x == 1L<<i)
      return 1;
  }
  return 0;
}
//4
long test_allAsciiDigits(long x) {
    int i;
    long ok = 1;
    for (i = 0; i < 64; i+=8) {
        long b = (x >> i) & 0xFF;
        ok = ok && (0x30 <= b) && (b <= 0x39);
    }
    return ok;
}
long test_trueThreeFourths(long x)
{
  return (long) (((__int128) x * 3L)/4L);
}
long test_bitCount(long x) {
  long result = 0;
  long i;
  for (i = 0; i < 64; i++)
    result += (x >> i) & 0x1;
  return result;
}
