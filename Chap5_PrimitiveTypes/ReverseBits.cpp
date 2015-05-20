/*++++++++++++++++++++++++++++++++++++++++++++++++
 * File:   ReverseBits.cpp
 * Author: Bharathwaj Sankara
 * wajsankara at yahoo dot com
 *++++++++++++++++++++++++++++++++++++++++++++++++*/


/* Takes a 64-bit integer x and reverse its bits */
/* Implemented in C++, because easier for bit manipulation in C++ */

/*---------------------------------------------------------------------------------------
 * Strategy:
 *---------------------------------------------------------------------------------------*/

/*
 * OPTION 1 (NOT EFFICIENT BUT OBVIOUS) 
 -- Run a loop for the length of the integer
 -- Swap the bits.
 -- Complexity is O(n)

 * OPTION 2 (EFFECIENT USING LOOKUP TABLE)
 -- A simpler approach will be with lookup table
 -- For 64-bits lookup table is expensive.
 -- So split this operation into 4 16-bit chunk

     .-------+-------+-------+-------.
 A = | 63:48 | 47:32 | 31:16 | 15:0  |
     .-------+-------+-------+-------.
  
  -- Lookup the table with each of the 4 chunks
  -- Each lookup results in the bit-reversed value for each of the chunk
  -- Then layout the result this way

     .-------+-------+-------+-------.
 R = | 15:0  | 31:16 | 47:32 | 63:48 |
     .-------+-------+-------+-------.
 
   -- This is much faster.

 */

#include <stdio.h>
#include <stdint.h>

uint64_t swapBits(uint64_t v, int i, int j)
{
  uint64_t x = v;
  if (((x  >> i) & 0x1) != ((x >> j) & 0x1))  {
    x ^= (1ULL << i) | (1ULL << j);
  }
  return x;
}

int reverseBitsSwap(uint64_t x) {
  uint64_t v = x;
  for (int i = 0; i < 32; ++i) {
    x = swapBits (x, i, 63-i);
  } 
}

int reverseBitsLookup(uint64_t x) {
  uint64_t v = 0;

}

int main ()
{
  printf ("1. 0x000000000000FFFF (31, 15): 0x%llx\n", swapBits(0x000000000000FFFF , 31, 15));
  printf ("1. 0x00000000F000F000 (63, 31): 0x%llx\n", swapBits(0x00000000F000F000 , 63, 31));
  printf ("1. 0xAAAAAAAAAAAAAAAA (1, 63): 0x%llx\n",  swapBits(0xAAAAAAAAAAAAAAAA , 31, 15));
}
