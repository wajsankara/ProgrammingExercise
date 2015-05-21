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

/* 
 * for simplicity, using 4-bit lookup, modenr machines can use 16-bit lookup,
 * but generating 64K tables will be painful, 4-bit lookup is easier to demo 
 */

int precomputed[16] = {
  0x0,/* 0000 -> 0000 */
  0x8,/* 0001 -> 1000 */
  0x4,/* 0010 -> 0100 */
  0xC,/* 0011 -> 1100 */
  0x2,/* 0100 -> 0010 */
  0xA,/* 0101 -> 1010 */
  0x6,/* 0110 -> 0110 */
  0xE,/* 0111 -> 1110 */
  0x1,/* 1000 -> 0001 */
  0x9,/* 1001 -> 1001 */
  0x5,/* 1010 -> 0101 */
  0xD,/* 1011 -> 1101 */
  0x3,/* 1100 -> 0011 */
  0xB,/* 1101 -> 1011 */
  0x7,/* 1110 -> 0111 */
  0xF /* 1111 -> 1111 */
};

/* Reverse Bits using Swapping */

uint64_t reverseBitsSwap(uint64_t x) {
  uint64_t v = x;
  for (int i = 0; i < 32; ++i) {
    v = swapBits (v, i, 63-i);
  } 
  return v;
}

/* Reverse Bits using Lookup Table */

uint64_t reverseBitsLookup(uint64_t x) {
  uint64_t v = 0UL;
  uint64_t m = 0xFUL;
  for (int i = 0; i < 64; i=i+4)
  {
    uint64_t val = (x & (m << i)) >> i;
    uint64_t val_rev = precomputed[val];
    v |= val_rev << (60 - i);
  }
  return v;
}

int main ()
{
  printf ("1A. 0xFFFF00000000FFFF : 0x%016llx\n", reverseBitsLookup(0xFFFF00000000FFFF));
  printf ("1B. 0xFFFF00000000FFFF : 0x%016llx\n", reverseBitsSwap(0xFFFF00000000FFFF));
  printf ("2A. 0xAA000000F000F000 : 0x%016llx\n", reverseBitsLookup(0xAA000000F000F000));
  printf ("2B. 0xAA000000F000F000 : 0x%016llx\n", reverseBitsSwap(0xAA000000F000F000));
  printf ("3A. 0xAAAAAAAAAAAAAAAA : 0x%016llx\n", reverseBitsLookup(0xAAAAAAAAAAAAAAAA));
  printf ("3B. 0xAAAAAAAAAAAAAAAA : 0x%016llx\n", reverseBitsSwap(0xAAAAAAAAAAAAAAAA));
}

/* **MAJOR ISSUES**
 * 1. Ensure all the intermediate values use the right sized variables. 
 *    Used 32-bit vars for m and val_rev. Causes truncation
 * 2. Line 92, should shift by the right amount (60-i and not 63-i).
 */

