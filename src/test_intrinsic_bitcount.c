/*
 * test_intrinsic_bitcount.c
 *
 * This file was part of the Independent JPEG Group's software:
 * Copyright (C) 1991-1997, Thomas G. Lane.
 * libjpeg-turbo Modifications:
 * Copyright (C) 2019, 2022, D. R. Commander.
 * For conditions of distribution and use, see the accompanying README.ijg
 * file.
 *
 * This file tests the selected intrinsic against a known-good table
 * to esnure the intrinsic is operating as intended.
 */

#include <stdio.h>
#include <stdlib.h>

#include "monolithic_examples.h"

#include "jpeg_nbits.h"

#define HIDDEN                           static
#define INCLUDE_JPEG_NBITS_TABLE

#include "jpeg_nbits.c"


#if defined(BUILD_MONOLITHIC)
#define main   tj_test_intrinsic_bitcount_main
#endif

int main(void)
{
	int rv = 0;
	int i = 0;

	{
		int a2 = JPEG_NBITS(i);

		int b1 = jpeg_nbits_table[i];

		if (a2 != b1) {
			fprintf(stderr, "nbit intrinsic failed at value %d: %d <-> %d\n", i, a2, b1);
			rv = 1;
		}
	}

	for (i = 1; i < 65536; i++) {
		int a1 = JPEG_NBITS_NONZERO(i);
		int a2 = JPEG_NBITS(i);

		int b1 = jpeg_nbits_table[i];

		if (a1 != b1) {
			fprintf(stderr, "nonzero intrinsic failed at value %d: %d <-> %d\n", i, a1, b1);
			rv = 1;
		}
		if (a2 != b1) {
			fprintf(stderr, "nbit intrinsic failed at value %d: %d <-> %d\n", i, a2, b1);
			rv = 1;
		}
	}

	return rv;
}
