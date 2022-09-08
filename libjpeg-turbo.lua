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
  "jsimd_none.c",
  "jutils.c",
}

if (_PLATFORM_WINUWP) then
  defines {
    "_CRT_SECURE_NO_WARNINGS",
  }
end
