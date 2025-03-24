#ifndef _GEM_DYN_BISET_H
#define _GEM_DYN_BISET_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Dynamic bitset (when trying to modify a bit out of bounds it reallocates enough to get to it)
typedef struct {
    uint8_t   *data;  // array of chars (bytes) that stores bits
    uint8_t _chunks;  // number of chunks (bytes) allocated.
                           // _chunks is initialized as 1... why ? no fucking idea...
    uint8_t  _start;  // offset of the first chunk in the bitset to save memory
} dyn_bitset;

#define CHUNK_INDEX(I) ((unsigned int)(I/8))  // Get index of the chunk from index of a bit
#define DEFAULT_DB {.data=NULL,._chunks=0, ._start=0}

bool bget(dyn_bitset* bs, uint32_t index); //returns the state of a specific bit in a bitset as boolean

int _brealloc(dyn_bitset* bs, uint32_t index);

void bflip(dyn_bitset* bs, uint32_t index); // flips the state of a bit, reallocating memory if the bit to flip is outside of the bounds

int bset(dyn_bitset* bs, uint32_t index, uint8_t val);

void bdel(dyn_bitset* bs); // free the array of bytes & sets the number of allocated chunks back to 0

#endif
