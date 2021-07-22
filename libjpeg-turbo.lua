project "jpeg"

dofile(_BUILD_DIR .. "/static_library.lua")

configuration { "*" }

uuid "9A746419-F4A6-4D7A-8819-689F1F12C3AF"

includedirs {
  ".",
}

files {
  "jaricom.c",
  "jcapimin.c",
  "jcapistd.c",
  "jcarith.c",
  "jccoefct.c",
  "jccolor.c",
  "jcdctmgr.c",
  "jchuff.c",
  "jcinit.c",
  "jcmainct.c",
  "jcmarker.c",
  "jcmaster.c",
  "jcomapi.c",
  "jcparam.c",
  "jcphuff.c",
  "jcprepct.c",
  "jcsample.c",
  "jctrans.c",
  "jdapimin.c",
  "jdapistd.c",
  "jdarith.c",
  "jdatadst.c",
  "jdatasrc.c",
  "jdcoefct.c",
  "jdcolor.c",
  "jddctmgr.c",
  "jdhuff.c",
  "jdinput.c",
  "jdmainct.c",
  "jdmarker.c",
  "jdmaster.c",
  "jdmerge.c",
  "jdphuff.c",
  "jdpostct.c",
  "jdsample.c",
  "jdtrans.c",
  "jerror.c",
  "jfdctflt.c",
  "jfdctfst.c",
  "jfdctint.c",
  "jidctflt.c",
  "jidctfst.c",
  "jidctint.c",
  "jidctred.c",
  "jmemmgr.c",
  "jmemnobs.c",
  "jquant1.c",
  "jquant2.c",
  "jutils.c",
}

local opts_simd_none = {
  "jsimd_none.c",
}

local opts_simd_arm_base = {
  "simd/arm/jcgray-neon.c",
  "simd/arm/jcsample-neon.c",
  "simd/arm/jdcolor-neon.c",
  "simd/arm/jdsample-neon.c",
  "simd/arm/jdmerge-neon.c",
  "simd/arm/jquanti-neon.c",
  "simd/arm/jfdctfst-neon.c",
  "simd/arm/jfdctint-neon.c",
  "simd/arm/jidctred-neon.c",
  "simd/arm/jidctfst-neon.c",
  "simd/arm/jcphuff-neon.c",
}

local opts_simd_arm32 = {
  opts_simd_arm_base,
  "simd/arm/aarch32/jchuff-neon.c",
  "simd/arm/aarch32/jsimd_neon.S",
  "simd/arm/aarch32/jsimd.c",
}

local opts_simd_arm64 = {
  opts_simd_arm_base,
  "simd/arm/aarch32/jchuff-neon.c",
  "simd/arm/aarch64/jsimd_neon.S",
  "simd/arm/aarch64/jsimd.c",
}

if (_PLATFORM_ANDROID) then
  configuration { "*arm64*" }

  defines {
    "WITH_SIMD",
  }

  includedirs {
    "simd/arm",
  }

  files {
    opts_simd_arm64,
  }

  configuration { "*armv7*" }

  defines {
    "WITH_SIMD",
  }

  includedirs {
    "simd/arm",
  }

  files {
    opts_simd_arm32,
  }

  configuration { "*x64*" }

  files {
    opts_simd_none,
  }

  configuration { "*x86*" }

  files {
    opts_simd_none,
  }
end

if (_PLATFORM_COCOA) then
  configuration { "*arm64*" }

  defines {
    "WITH_SIMD",
  }

  includedirs {
    "simd/arm",
  }

  files {
    opts_simd_arm64,
  }

  configuration { "*x64*" }

  files {
    opts_simd_none,
  }
end

if (_PLATFORM_IOS) then
  configuration { "*arm64*" }

  defines {
    "WITH_SIMD",
  }

  includedirs {
    "simd/arm",
  }

  files {
    opts_simd_arm64,
  }

  configuration { "*x64*" }

  files {
    opts_simd_none,
  }
end

if (_PLATFORM_LINUX) then
  files {
    opts_simd_none,
  }
end

if (_PLATFORM_MACOS) then
  files {
    opts_simd_none,
  }
end

if (_PLATFORM_WINDOWS) then
  defines {
    "TURBO_FOR_WINDOWS",
  }

  files {
    opts_simd_none,
  }
end

if (_PLATFORM_WINUWP) then
  defines {
    "TURBO_FOR_WINDOWS",
    "_CRT_SECURE_NO_WARNINGS",
  }

  files {
    opts_simd_none,
  }
end
