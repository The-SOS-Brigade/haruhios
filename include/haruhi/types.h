#ifndef _HARUHI_TYPES_H
#define _HARUHI_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef _Bool bool;

typedef __builtin_va_list va_list;
#define va_start(v, n) __builtin_va_start(v, n)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, t) __builtin_va_arg(v, t)

#endif

