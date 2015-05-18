/* Takes a 64-bit integer x and swaps bit i and bits j */
/* Implemented in C++, because easier for bit manipulation in C++ */

/*---------------------------------------------------------------------------------------
 * Strategy:
 *---------------------------------------------------------------------------------------*/

/*
 -- Check if the bits are same, nothing to do
 -- Else toggle the bits
 */

#include <stdio.h>
#include <stdint.h>

uint64_t swapBits(uint64_t v, int i, int j)
{
  uint64_t x = v;
  if (((x  >> i) & 0x1) != ((x >> j) & 0x1))  {
    x ^= (1 << i) | (1 << j);
  }
  return x;
}

int main ()
{
  printf ("1. 0x000000000000FFFF (31, 15): 0x%llx\n", swapBits(0x000000000000FFFF , 31, 15));
  printf ("1. 0x00000000F000F000 (63, 31): 0x%llx\n", swapBits(0x00000000F000F000 , 31, 15));
  printf ("1. 0xAAAAAAAAAAAAAAAA (1, 63): 0x%llx\n",  swapBits(0xAAAAAAAAAAAAAAAA , 31, 15));
}
