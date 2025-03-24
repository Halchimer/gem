#ifndef _GEM_VECTOR_H
#define _GEM_VECTOR_H

#include <stdint.h>
#include "gem_utils.h"

#define _GEM_DEFINE_VECTOR2_TYPE(T) struct { T x;T y; }
#define _GEM_DEFINE_VECTOR3_TYPE(T) struct { T x;T y;T z; }
#define _GEM_DEFINE_VECTOR4_TYPE(T) struct { T x;T y;T z; T w; }

/*
*   Vector 2 defs
*/

typedef _GEM_DEFINE_VECTOR2_TYPE(int8_t) vec2i8_t;
typedef _GEM_DEFINE_VECTOR2_TYPE(int16_t) vec2i16_t;
typedef _GEM_DEFINE_VECTOR2_TYPE(int32_t) vec2i_t;
typedef _GEM_DEFINE_VECTOR2_TYPE(int64_t) vec2i64_t;

typedef _GEM_DEFINE_VECTOR2_TYPE(uint8_t) vec2u8_t, vec2b_t;
typedef _GEM_DEFINE_VECTOR2_TYPE(uint16_t) vec2u16_t;
typedef _GEM_DEFINE_VECTOR2_TYPE(uint32_t) vec2u_t;
typedef _GEM_DEFINE_VECTOR2_TYPE(uint64_t) vec2u64_t;

typedef _GEM_DEFINE_VECTOR2_TYPE(float) vec2f_t;
typedef _GEM_DEFINE_VECTOR2_TYPE(double) vec2d_t, vec2f64_t;

/*
*   Vector 3 defs
*/

typedef _GEM_DEFINE_VECTOR3_TYPE(int8_t) vec3i8_t;
typedef _GEM_DEFINE_VECTOR3_TYPE(int16_t) vec3i16_t;
typedef _GEM_DEFINE_VECTOR3_TYPE(int32_t) vec3i_t;
typedef _GEM_DEFINE_VECTOR3_TYPE(int64_t) vec3i64_t;

typedef _GEM_DEFINE_VECTOR3_TYPE(uint8_t) vec3u8_t, vec3b_t;
typedef _GEM_DEFINE_VECTOR3_TYPE(uint16_t) vec3u16_t;
typedef _GEM_DEFINE_VECTOR3_TYPE(uint32_t) vec3u_t;
typedef _GEM_DEFINE_VECTOR3_TYPE(uint64_t) vec3u64_t;

typedef _GEM_DEFINE_VECTOR3_TYPE(float) vec3f_t;
typedef _GEM_DEFINE_VECTOR3_TYPE(double) vec3d_t, vec3f64_t;

/*
*   Vector 4 defs
*/

typedef _GEM_DEFINE_VECTOR4_TYPE(int8_t) vec4i8_t;
typedef _GEM_DEFINE_VECTOR4_TYPE(int16_t) vec4i16_t;
typedef _GEM_DEFINE_VECTOR4_TYPE(int32_t) vec4i_t;
typedef _GEM_DEFINE_VECTOR4_TYPE(int64_t) vec4i64_t;

typedef _GEM_DEFINE_VECTOR4_TYPE(uint8_t) vec4u8_t, vec4b_t;
typedef _GEM_DEFINE_VECTOR4_TYPE(uint16_t) vec4u16_t;
typedef _GEM_DEFINE_VECTOR4_TYPE(uint32_t) vec4u_t;
typedef _GEM_DEFINE_VECTOR4_TYPE(uint64_t) vec4u64_t;

typedef _GEM_DEFINE_VECTOR4_TYPE(float) vec4f_t;
typedef _GEM_DEFINE_VECTOR4_TYPE(double) vec4d_t, vec4f64_t;

#define VECN(N, ...) VEC##N(__VA_ARGS__)
#define VECNA(N, ...) VECN(N, __VA_ARGS__)
#define VEC(...) VECNA(PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define VEC4(...) _Generic((GEM_FIRST(__VA_ARGS__)),    \
    int : (vec4i_t){__VA_ARGS__},                       \
    uint32_t : (vec4u_t){__VA_ARGS__},                  \
    float : (vec4f_t){__VA_ARGS__},                     \
    double : (vec4d_t){__VA_ARGS__}                     \
)

#define VEC3(...) _Generic((GEM_FIRST(__VA_ARGS__)),    \
    int : (vec3i_t){__VA_ARGS__},                       \
    uint32_t : (vec3u_t){__VA_ARGS__},                  \
    float : (vec3f_t){__VA_ARGS__},                     \
    double : (vec3d_t){__VA_ARGS__}                     \
)

#define VEC2(...) _Generic((GEM_FIRST(__VA_ARGS__)),    \
    int : (vec2i_t){__VA_ARGS__},                       \
    uint32_t : (vec2u_t){__VA_ARGS__},                  \
    float : (vec2f_t){__VA_ARGS__},                     \
    double : (vec2d_t){__VA_ARGS__}                     \
)

/*
*   Vector math
*/

#define VEC4SUM(A, B) {A.x+B.x, A.y+B.y, A.z+B.z, A.w+B.w}
#define VEC3SUM(A, B) {A.x+B.x, A.y+B.y, A.z+B.z}
#define VEC2SUM(A, B) {A.x+B.x, A.y+B.y}

#define DOT4(A, B) (A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w)
#define DOT3(A, B) (A.x*B.x + A.y*B.y + A.z*B.z)
#define DOT2(A, B) (A.x*B.x + A.y*B.y)

#define CROSS3(A, B) {(A.y*B.z - B.y*A.z),(A.z*B.x - B.z*A.x), (A.x*B.y - B.x*A.y)}

#define MUL4(S, V) {S*V.x, S*V.y, S*V.z, S*V.w}
#define MUL3(S, V) {S*V.x, S*V.y, S*V.z}
#define MUL2(S, V) {S*V.x, S*V.y}

#endif
