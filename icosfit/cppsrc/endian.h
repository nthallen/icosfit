/*
 * This file can be added to your source directory if your system
 * does not have an endian.h and your architecture is LITTLE ENDIAN
 * (e.g. Intel processors).
 */
#ifndef ENDIAN_H_INCLUDED
#define ENDIAN_H_INCLUDED

#define BIG_ENDIAN 4321
#define LITTLE_ENDIAN 1234
#define BYTE_ORDER LITTLE_ENDIAN

#endif
