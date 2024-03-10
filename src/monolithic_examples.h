
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
	extern int jpegturbo_tjexample_main(int argc, const char** argv);
	extern int jpegturbo_tjunittest_main(int argc, const char** argv);
	extern int jpegturbo_wrjpgcom_main(int argc, const char** argv);
	extern int tj_test_intrinsic_bitcount_main(void);

#ifdef __cplusplus
}
#endif

#endif
