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

local opts_simd_arm = {
  "simd/arm/jsimd_arm.c",
  "simd/arm/jsimd_neon_arm.S",
}

local opts_simd_arm64 = {
  "simd/arm64/jsimd_arm64.c",
  "simd/arm64/jsimd_neon_arm64.S",
}

if (_PLATFORM_ANDROID) then
  configuration { "*arm64*" }

  defines {
    "WITH_SIMD",
  }

  files {
    opts_simd_arm64,
  }

  configuration { "*armv7*" }

  defines {
    "WITH_SIMD",
  }

  files {
    opts_simd_arm,
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
