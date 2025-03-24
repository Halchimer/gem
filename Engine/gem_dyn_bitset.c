#include "gem_dyn_bitset.h"

//
//      Dynamic Bitsets
//
bool bget(dyn_bitset* bs, uint32_t index) //returns the state of a specific bit in a bitset as boolean
{
    return CHUNK_INDEX(index)<bs->_start||(CHUNK_INDEX(index) - bs->_start)>=bs->_chunks?false:(bs->data[CHUNK_INDEX(index) - bs->_start]&(1 << (index%8)))!=0;
    // when the index of a bit is outside of any allocated chunk (chunk index > number of chunks) then the bit is always 0, hence the condition
}

int _brealloc(dyn_bitset* bs, uint32_t index)
{
    if(bs->_chunks == 0)
    {
        bs->data = (uint8_t*)calloc(1, sizeof(uint8_t));
        bs->_start = CHUNK_INDEX(index);
        bs->_chunks = 1;
    }
    else
    {
        if(CHUNK_INDEX(index)<bs->_start)
        {
            bs->data = (uint8_t*)realloc(bs->data, (bs->_chunks + bs->_start - CHUNK_INDEX(index))*sizeof(uint8_t));
            uint8_t* temp_ptr = (uint8_t*)calloc(bs->_chunks + bs->_start - CHUNK_INDEX(index), sizeof(uint8_t));
            memcpy(temp_ptr + bs->_start - CHUNK_INDEX(index), bs->data, bs->_chunks*sizeof(uint8_t));
            free(bs->data);
            bs->data = temp_ptr;
            bs->_chunks += bs->_start - CHUNK_INDEX(index);
            bs->_start = CHUNK_INDEX(index);
        }
        else if((CHUNK_INDEX(index) - bs->_start)>=bs->_chunks)
        {
            bs->data = (uint8_t*)realloc(bs->data, (CHUNK_INDEX(index) - bs->_start + 1)*sizeof(uint8_t));
            bs->_chunks = CHUNK_INDEX(index) + 1;
        }
    }

    return (int)(bs->data!=NULL);
}

void bflip(dyn_bitset* bs, uint32_t index) // flips the state of a bit, reallocating memory if the bit to flip is outside of the bounds
{
    _brealloc(bs, index);

    bs->data[CHUNK_INDEX(index) - bs->_start] ^= (1 << (index%8));
}

int bset(dyn_bitset* bs, uint32_t index, uint8_t val) // val = 0 or 1
{
    _brealloc(bs, index);
    switch(val)
    {
    case 1 :
        bs->data[CHUNK_INDEX(index) - bs->_start] |= (1 << (index%8));
        break;
    case 0:
        bs->data[CHUNK_INDEX(index) - bs->_start] &= ~(1 << (index%8));
        break;
    default:
        printf("gem | Dynamic Bitset : value passed to bset must be either 1 or 0.");
        return -1;
    }
}

void bdel(dyn_bitset* bs) // free the array of bytes & sets the number of allocated chunks back to 0
{
    free(bs->data);
    bs->_chunks = 0;
}
