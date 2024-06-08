/*
 * Risc-V vector extension optimizations for libjpeg-turbo
 *
 * Copyright (C) 2014, D. R. Commander.  All Rights Reserved.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

/* RGB --> GRAYSCALE CONVERSION */
#include "jsimd_rvv.h"

/* RGB -> GRAYSCALE CONVERSION constants */
#define F_0_114  7471                 /* FIX(0.11400) */
#define F_0_299  19595                /* FIX(0.29900) */
#define F_0_587  38470                /* FIX(0.58700) */

#define SCALEBITS  16
#define ONE_HALF  (1 << (SCALEBITS - 1))


#ifndef RGB_PIXELSIZE
#error "RGB_PIXELSIZE must be defined"
#endif

#include "jcgryext-rvv.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE

#define RGB_RED  EXT_RGB_RED
#define RGB_GREEN  EXT_RGB_GREEN
#define RGB_BLUE  EXT_RGB_BLUE
#define RGB_PIXELSIZE  EXT_RGB_PIXELSIZE
#define jsimd_rgb_gray_convert_rvv  jsimd_extrgb_gray_convert_rvv
#include "jcgryext-rvv.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_gray_convert_rvv

#define RGB_RED  EXT_RGBX_RED
#define RGB_GREEN  EXT_RGBX_GREEN
#define RGB_BLUE  EXT_RGBX_BLUE
#define RGB_PIXELSIZE  EXT_RGBX_PIXELSIZE
#define jsimd_rgb_gray_convert_rvv  jsimd_extrgbx_gray_convert_rvv
#include "jcgryext-rvv.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_gray_convert_rvv

#define RGB_RED  EXT_BGR_RED
#define RGB_GREEN  EXT_BGR_GREEN
#define RGB_BLUE  EXT_BGR_BLUE
#define RGB_PIXELSIZE  EXT_BGR_PIXELSIZE
#define jsimd_rgb_gray_convert_rvv  jsimd_extbgr_gray_convert_rvv
#include "jcgryext-rvv.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_gray_convert_rvv

#define RGB_RED  EXT_BGRX_RED
#define RGB_GREEN  EXT_BGRX_GREEN
#define RGB_BLUE  EXT_BGRX_BLUE
#define RGB_PIXELSIZE  EXT_BGRX_PIXELSIZE
#define jsimd_rgb_gray_convert_rvv  jsimd_extbgrx_gray_convert_rvv
#include "jcgryext-rvv.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_gray_convert_rvv

#define RGB_RED  EXT_XBGR_RED
#define RGB_GREEN  EXT_XBGR_GREEN
#define RGB_BLUE  EXT_XBGR_BLUE
#define RGB_PIXELSIZE  EXT_XBGR_PIXELSIZE
#define jsimd_rgb_gray_convert_rvv  jsimd_extxbgr_gray_convert_rvv
#include "jcgryext-rvv.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_gray_convert_rvv

#define RGB_RED  EXT_XRGB_RED
#define RGB_GREEN  EXT_XRGB_GREEN
#define RGB_BLUE  EXT_XRGB_BLUE
#define RGB_PIXELSIZE  EXT_XRGB_PIXELSIZE
#define jsimd_rgb_gray_convert_rvv  jsimd_extxrgb_gray_convert_rvv
#include "jcgryext-rvv.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_gray_convert_rvv
