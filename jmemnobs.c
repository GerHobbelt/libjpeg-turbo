/*
 * jmemnobs.c
 *
 * This file was part of the Independent JPEG Group's software:
 * Copyright (C) 1992-1996, Thomas G. Lane.
 * libjpeg-turbo Modifications:
 * Copyright (C) 2017-2018, D. R. Commander.
 * For conditions of distribution and use, see the accompanying README.ijg
 * file.
 *
 * This file provides a really simple implementation of the system-
 * dependent portion of the JPEG memory manager.  This implementation
 * assumes that no backing-store files are needed: all required space
 * can be obtained from malloc().
 * This is very portable in the sense that it'll compile on almost anything,
 * but you'd better have lots of main memory (or virtual memory) if you want
 * to process big images.
 */

#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"
#include "jmemsys.h"            /* import the system-dependent declarations */


/*
 * Memory allocation and freeing are controlled by the regular library
 * routines malloc() and free().
 */

static void *
jpeg_get_small(j_common_ptr cinfo, size_t sizeofobject)
{
  return (void *)malloc(sizeofobject);
}

static void
jpeg_free_small(j_common_ptr cinfo, void *object, size_t sizeofobject)
{
  free(object);
}


/*
 * "Large" objects are treated the same as "small" ones.
 */

static void *
jpeg_get_large(j_common_ptr cinfo, size_t sizeofobject)
{
  return (void *)malloc(sizeofobject);
}

static void
jpeg_free_large(j_common_ptr cinfo, void *object, size_t sizeofobject)
{
  free(object);
}


/*
 * This routine computes the total memory space available for allocation.
 */

static size_t
jpeg_mem_available(j_common_ptr cinfo, size_t min_bytes_needed,
                   size_t max_bytes_needed, size_t already_allocated)
{
  if (cinfo->mem->max_memory_to_use) {
    if ((size_t)cinfo->mem->max_memory_to_use > already_allocated)
      return cinfo->mem->max_memory_to_use - already_allocated;
    else
      return 0;
  } else {
    /* Here we always say, "we got all you want bud!" */
    return max_bytes_needed;
  }
}


/*
 * Backing store (temporary file) management.
 * Since jpeg_mem_available always promised the moon,
 * this should never be called and we can just error out.
 */

static void
jpeg_open_backing_store(j_common_ptr cinfo, backing_store_ptr info,
                        long total_bytes_needed)
{
  ERREXIT(cinfo, JERR_NO_BACKING_STORE);
}


/*
 * These routines take care of any system-dependent initialization and
 * cleanup required.  Here, there isn't any.
 */

static long
jpeg_mem_init(j_common_ptr cinfo)
{
  return 0;                     /* just set max_memory_to_use to 0 */
}

static void
jpeg_mem_term(j_common_ptr cinfo)
{
  /* no work */
}

// ---------------------------------------------------------

static jpeg_sys_mem_register_t *default_cinfo_client_callback = NULL;

int jpeg_nobs_sys_mem_register(j_common_ptr cinfo)
{
	// execute user specified global default setup function?
	if (default_cinfo_client_callback)
		return default_cinfo_client_callback(cinfo);

	// no user-speecified setup provided: usee the default
	// we defined above instead.

	cinfo->sys_mem_if.get_small = jpeg_get_small;
	cinfo->sys_mem_if.free_small = jpeg_free_small;

	cinfo->sys_mem_if.get_large = jpeg_get_large;
	cinfo->sys_mem_if.free_large = jpeg_free_large;

	cinfo->sys_mem_if.mem_available = jpeg_mem_available;

	cinfo->sys_mem_if.open_backing_store = jpeg_open_backing_store;

	cinfo->sys_mem_if.mem_init = jpeg_mem_init;
	cinfo->sys_mem_if.mem_term = jpeg_mem_term;

	return 0;
}

void jpeg_sys_mem_set_default_setup(jpeg_sys_mem_register_t *client_callback)
{
	// NULL is handled automatically as jpeg_nobs_sys_mem_register() will
	// use a deefault implementation then:
	default_cinfo_client_callback = client_callback;
}
