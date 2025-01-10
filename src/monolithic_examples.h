
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

	extern int jpegturbo_cjpeg_main(int argc, const char** argv);
	extern int jpegturbo_djpeg_main(int argc, const char** argv);
	extern int jpegturbo_jcstest_main(int argc, const char** argv);
	extern int jpegturbo_jpegtran_main(int argc, const char** argv);
	extern int jpegturbo_md5cmp_main(int argc, const char** argv);
	extern int jpegturbo_rdjpegcom_main(int argc, const char** argv);
	extern int jpegturbo_tjbench_main(int argc, const char** argv);
	extern int jpegturbo_tjcomp_main(int argc, const char** argv);
	extern int jpegturbo_tjdecomp_main(int argc, const char** argv);
	extern int jpegturbo_tjunittest_main(int argc, const char** argv);
	extern int jpegturbo_wrjpgcom_main(int argc, const char** argv);
	extern int tj_test_intrinsic_bitcount_main(void);
	extern int jpegturbo_md5sum_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
