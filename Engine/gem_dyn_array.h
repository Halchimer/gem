#ifndef _GEM_DYN_ARRAY_H
#define _GEM_DYN_ARRAY_H

/*
*   DEPRECATED
*/

#ifndef DYN_ARRAY_CHUNK_SIZE
#define DYN_ARRAY_CHUNK_SIZE 10
#endif

#include "gem_utils.h"

#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

#define INIT_ARRAY_TYPE(T) typedef struct{T *_data; unsigned int size; unsigned int _chunk_n;unsigned int _element_size;} dyn_arr_##T;
#define DYN_ARR_NEW(T) {NULL, 0, 0, sizeof(T)}

#define DYN_ADD(A, V) if(A._data == NULL) {A._data = calloc(DYN_ARRAY_CHUNK_SIZE, A._element_size);A._chunk_n=1;} \
                   if((unsigned int)((A.size + 1) / DYN_ARRAY_CHUNK_SIZE) > A._chunk_n) {A._data = realloc(A._data, (A._chunk_n+1) * A._element_size);A._chunk_n++;} \
                   A._data[A.size] = V;A.size++;

#define DYN_REM(A, I) if(I>=A.size || I < 0) printf("gem | Dynamic Array : index out of bounds ( at line %d )\n", __LINE__); \
                      memmove(A._data+I, A._data+I+1, (A.size-(I+1))*A._element_size);A.size--; \
                      if((unsigned int)(A.size / DYN_ARRAY_CHUNK_SIZE) < A._chunk_n) {A._data = realloc(A._data, (A._chunk_n-1) * DYN_ARRAY_CHUNK_SIZE* A._element_size);A._chunk_n--;}

#define DYN_GET(A, I) (((I<A.size)&&(I>=0))?A._data[I]:printf("gem | Dynamic Array : index out of bounds ( at line %d )\n", __LINE__))

#define FREE_DYN_ARR(A) free(A._data);A.size=0;A._chunk_n=0;

#define DYN_SET(A, V) if(A._data == NULL){FREE_DYN_ARR(A)} A._data = V;A.size=sizeof(V)/sizeof(V[0]);A._chunk_n = CEIL(A.size / DYN_ARRAY_CHUNK_SIZE);

// Default array types

[[deprecated]]
INIT_ARRAY_TYPE(char)
[[deprecated]]
INIT_ARRAY_TYPE(short)
[[deprecated]]
INIT_ARRAY_TYPE(int)
[[deprecated]]
INIT_ARRAY_TYPE(long)
[[deprecated]]
INIT_ARRAY_TYPE(float)
[[deprecated]]
INIT_ARRAY_TYPE(double)

#endif
