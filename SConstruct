import sys
import datetime
import excons

env = excons.MakeBaseEnv(output_dir="./scons-build")

out_incdir = excons.OutputBaseDirectory() + "/include"
out_libdir = excons.OutputBaseDirectory() + "/lib"

if sys.platform == "win32":
   options = {"WITH_SIMD"      : excons.GetArgument("with-simd",       1, int),
              "WITH_ARITH_ENC" : excons.GetArgument("with-arith-enc",  1, int),
              "WITH_ARITH_DEC" : excons.GetArgument("with-arith-dec",  1, int),
              "WITH_JPEG7"     : excons.GetArgument("with-jpeg7",      0, int),
              "WITH_JPEG8"     : excons.GetArgument("with-jpeg8",      0, int),
              "WITH_MEM_SRCDST": excons.GetArgument("with-mem-srcdst", 1, int),
              "WITH_TURBOJPEG" : excons.GetArgument("with-turbojpeg",  1, int),
              "WITH_12BIT"     : excons.GetArgument("with-12bit",      0, int)}

   if not env.CMakeConfigure("jpeg", opts=options):
      sys.exit(1)

   target = env.CMake(env.CMakeOutputs(),
                      env.CMakeInputs(dirs=[".", "simd", "md5"], patterns=[".c", ".h", ".h.in"]))

   env.CMakeClean()

else:
   options = {"--without-simd"      : excons.GetArgument("with-simd",      1, int) == 0,
              "--without-arith-enc" : excons.GetArgument("with-arith-enc", 1, int) == 0,
              "--without-arith-dec" : excons.GetArgument("with-arith-dec", 1, int) == 0,
              "--with-jpeg7"        : excons.GetArgument("with-jpeg7",     0, int) != 0,
              "--with-jpeg8"        : excons.GetArgument("with-jpeg8",     0, int) != 0,
              "--without-mem-srcdst": excons.GetArgument("with-arith-enc", 1, int) == 0,
              "--without-turbojpeg" : excons.GetArgument("with-arith-enc", 1, int) == 0,
              "--with-12bit"        : excons.GetArgument("with-12bit",     0, int) != 0}

   if not env.AutomakeConfigure("jpeg", opts=options):
      sys.exit(1)

   target = env.Automake(env.AutomakeOutputs(),
                         env.AutomakeInputs(dirs=[".", "simd", "md5"], patterns=[".c", ".h", ".h.in"]))

   env.AutomakeClean()


env.Alias("jpeg", target)
excons.SyncCache()


def RequireJpeg(env, static=False):
   # TODO
   pass

Export("RequireJpeg")
