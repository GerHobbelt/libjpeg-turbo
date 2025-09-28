/*
 * Copyright (C) 2014, 2021, 2024-2025, D. R. Commander.
 * Copyright (C) 2014, Olle Liljenzin.
 * Copyright (C) 2020, Arm Limited.
 *
 * For conditions of distribution and use, see the accompanying README.ijg
 * file.
 */

/*
 * NOTE: If USE_CLZ_INTRINSIC is defined, then clz/bsr instructions will be
 * used for bit counting rather than the lookup table.  This will reduce the
 * memory footprint by 64k, which is important for some mobile applications
 * that create many isolated instances of libjpeg-turbo (web browsers, for
 * instance.)  This may improve performance on some mobile platforms as well.
 * This feature is enabled by default only on Arm processors, because some x86
 * chips have a slow implementation of bsr, and the use of clz/bsr cannot be
 * shown to have a significant performance impact even on the x86 chips that
 * have a fast implementation of it.  When building for Armv6, you can
 * explicitly disable the use of clz/bsr by adding -mthumb to the compiler
 * flags (this defines __thumb__).
 */

#ifndef TURBO_JPEG_NBITS_H
#define TURBO_JPEG_NBITS_H


#ifndef USE_CLZ_INTRINSIC
 /* NOTE: Both GCC and Clang define __GNUC__ */
#if (defined(__GNUC__) && (defined(__arm__) || defined(__aarch64__))) || \
    defined(_M_ARM) || defined(_M_ARM64) || defined(_M_ARM64EC)
#if !defined(__thumb__) || defined(__thumb2__)
#define USE_CLZ_INTRINSIC
#endif
#endif
#if defined(_MSC_VER) && !defined(__clang__)
#include <intrin.h>
#define USE_CLZ_INTRINSIC
#endif
#endif

#ifdef USE_CLZ_INTRINSIC
#if defined(_MSC_VER) && !defined(__clang__)

// ripped from libbf & adapted to suit our needs:

static inline int __builtin_clnzl(unsigned long mask)
{
	unsigned long where;
	// Search from LSB to MSB for first set bit.
	// Returns zero if no set bit is found.
	if (_BitScanReverse(&where, mask))
		return 32 - 31 + (int)where;
	return 32 - 32; // Undefined Behavior.
}

static inline int __builtin_clnz(unsigned int x)
{
	return __builtin_clnzl(x);
}

#define JPEG_NBITS_NONZERO(x)  __builtin_clnz(x)
#else
#define JPEG_NBITS_NONZERO(x)  (32 - __builtin_clz(x))
#endif
#define JPEG_NBITS(x)          (x ? JPEG_NBITS_NONZERO(x) : 0)
#else
extern const unsigned char jpeg_nbits_table[65536];
#define JPEG_NBITS(x)          (jpeg_nbits_table[x])
#define JPEG_NBITS_NONZERO(x)  JPEG_NBITS(x)
#endif


#endif
