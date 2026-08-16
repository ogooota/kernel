#ifndef __GLOBAL_KDEFS_H
#define __GLOBAL_KDEFS_H

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

typedef signed char  int8;
typedef signed short int16;
typedef signed int   int32;

typedef unsigned char uchar;

_Static_assert(sizeof(uint8) == 1, "u8 expected to be 1 byte");
_Static_assert(sizeof(int16) == 2, "u16 expected to be 2 bytes");
_Static_assert(sizeof(uint32) == 4, "u32 expected to be 4 bytes");
_Static_assert(sizeof(int8) == 1, "i8 expected to be 1 byte");
_Static_assert(sizeof(int16) == 2, "i16 expected to be 2 bytes");
_Static_assert(sizeof(int32) == 4, "i32 expected to be 4 bytes");

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef EOF
#define EOF 0
#endif

#endif
