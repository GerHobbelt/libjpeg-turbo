# Anything that must be linked against the shared C library on Windows must
# be built in this subdirectory, because CMake doesn't allow us to override
# the compiler flags for each build type except at directory scope.  Note
# to CMake developers:  Add a COMPILE_FLAGS_<CONFIG> target property, or
# better yet, provide a friendly way of configuring a Windows target to use the
# static C library.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..)

if(MSVC_LIKE)
  # Build all configurations against shared C library
  if(WITH_CRT_DLL)
    if(CMAKE_VERSION VERSION_EQUAL "3.15" OR
      CMAKE_VERSION VERSION_GREATER "3.15")
      if(CMAKE_BUILD_TYPE_UC STREQUAL "DEBUG")
        set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDebugDLL)
    elseif(MSVC_IDE)
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
      else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
      endif()
      message(STATUS "Visual C++ run-time library for libjpeg API DLL: ${CMAKE_MSVC_RUNTIME_LIBRARY}")
    elseif(MSVC)
      foreach(var CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
        if(${var} MATCHES "/MT")
          string(REGEX REPLACE "/MT" "/MD" ${var} "${${var}}")
        endif()
      endforeach()
    endif()
  endif()
endif()

foreach(src ${JPEG_SOURCES})
  set(JPEG_SRCS ${JPEG_SRCS} ../${src})
endforeach()

if(WITH_SIMD AND (MSVC_IDE OR XCODE))
  # This tells CMake that the "source" files haven't been generated yet
  set_source_files_properties(${SIMD_OBJS} PROPERTIES GENERATED 1)
endif()

if(WIN32)
  set(DEFFILE ../win/jpeg${SO_MAJOR_VERSION}.def)
endif()
if(MSVC_LIKE)
  configure_file(${CMAKE_SOURCE_DIR}/win/jpeg.rc.in
    ${CMAKE_BINARY_DIR}/win/jpeg.rc)
  set(JPEG_SRCS ${JPEG_SRCS} ${CMAKE_BINARY_DIR}/win/jpeg.rc)
endif()
add_library(jpeg SHARED ${JPEG_SRCS} ${DEFFILE} ${SIMD_TARGET_OBJECTS}
  ${SIMD_OBJS} $<TARGET_OBJECTS:jpeg12> $<TARGET_OBJECTS:jpeg16>)

set_target_properties(jpeg PROPERTIES SOVERSION ${SO_MAJOR_VERSION}
  VERSION ${SO_MAJOR_VERSION}.${SO_AGE}.${SO_MINOR_VERSION})
if(APPLE AND (NOT CMAKE_OSX_DEPLOYMENT_TARGET OR
              CMAKE_OSX_DEPLOYMENT_TARGET VERSION_GREATER 10.4))
  if(NOT CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG)
    set(CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG "-Wl,-rpath,")
  endif()
  set_target_properties(jpeg PROPERTIES MACOSX_RPATH 1)
endif()
if(MAPFLAG)
  set_target_properties(jpeg PROPERTIES
    LINK_FLAGS "${MAPFLAG}${CMAKE_CURRENT_BINARY_DIR}/../libjpeg.map")
endif()
if(MSVC_LIKE)
  # Make it run from swap if running from CD/DVD or network
  set_target_properties(jpeg PROPERTIES LINK_FLAGS "/SWAPRUN:CD /SWAPRUN:NET")

  set_target_properties(jpeg PROPERTIES
    RUNTIME_OUTPUT_NAME jpeg${SO_MAJOR_VERSION})
  # The jsimd_*.c file is built to use libcmt or libcmtd, so this prevents a
  # linker warning.
  if(WITH_CRT_DLL)
    if(MSVC)
      set_target_properties(jpeg PROPERTIES LINK_FLAGS "/NODEFAULTLIB:LIBCMT /NODEFAULTLIB:LIBCMTD /SWAPRUN:CD /SWAPRUN:NET")
    else()
      set_target_properties(jpeg PROPERTIES LINK_FLAGS
        "-Wl,-nodefaultlib:libcmt -Wl,-nodefaultlib:libcmtd")
    endif()
  endif()
elseif(MINGW)
  set_target_properties(jpeg PROPERTIES SUFFIX -${SO_MAJOR_VERSION}.dll)
endif()

if(WIN32)
  set(USE_SETMODE "-DUSE_SETMODE")
endif()
set(CDJPEG_COMPILE_FLAGS
  "-DBMP_SUPPORTED -DGIF_SUPPORTED -DPPM_SUPPORTED -DTARGA_SUPPORTED ${USE_SETMODE}")

# Compile a separate version of these source files with 12-bit and 16-bit data
# precision.
add_library(cjpeg12 OBJECT ../src/rdppm.c)
set_property(TARGET cjpeg12 PROPERTY COMPILE_FLAGS
  "-DBITS_IN_JSAMPLE=12 -DGIF_SUPPORTED -DPPM_SUPPORTED")
add_library(cjpeg16 OBJECT ../src/rdppm.c)
set_property(TARGET cjpeg16 PROPERTY COMPILE_FLAGS
  "-DBITS_IN_JSAMPLE=16 -DGIF_SUPPORTED -DPPM_SUPPORTED")
add_executable(cjpeg ../src/cjpeg.c ../src/cdjpeg.c ../src/rdbmp.c
  ../src/rdgif.c ../src/rdppm.c ../src/rdswitch.c ../src/rdtarga.c
  $<TARGET_OBJECTS:cjpeg12> $<TARGET_OBJECTS:cjpeg16>)
set_property(TARGET cjpeg PROPERTY COMPILE_FLAGS ${CDJPEG_COMPILE_FLAGS})
target_link_libraries(cjpeg jpeg)

# Compile a separate version of these source files with 12-bit and 16-bit data
# precision.
add_library(djpeg12 OBJECT ../src/rdcolmap.c ../src/wrgif.c ../src/wrppm.c)
set_property(TARGET djpeg12 PROPERTY COMPILE_FLAGS
  "-DBITS_IN_JSAMPLE=12 -DGIF_SUPPORTED -DPPM_SUPPORTED")
add_library(djpeg16 OBJECT ../src/wrppm.c)
set_property(TARGET djpeg16 PROPERTY COMPILE_FLAGS
  "-DBITS_IN_JSAMPLE=16 -DPPM_SUPPORTED")
add_executable(djpeg ../src/djpeg.c ../src/cdjpeg.c ../src/rdcolmap.c
  ../src/rdswitch.c ../src/wrbmp.c ../src/wrgif.c ../src/wrppm.c
  ../src/wrtarga.c $<TARGET_OBJECTS:djpeg12> $<TARGET_OBJECTS:djpeg16>)
set_property(TARGET djpeg PROPERTY COMPILE_FLAGS ${CDJPEG_COMPILE_FLAGS})
target_link_libraries(djpeg jpeg)

add_executable(jpegtran ../src/jpegtran.c ../src/cdjpeg.c ../src/rdswitch.c
  ../src/transupp.c)
target_link_libraries(jpegtran jpeg)
set_property(TARGET jpegtran PROPERTY COMPILE_FLAGS "${USE_SETMODE}")

add_executable(example ../src/example.c)
target_link_libraries(example jpeg)

add_executable(jcstest ../src/jcstest.c)
target_link_libraries(jcstest jpeg)

install(TARGETS jpeg EXPORT ${CMAKE_PROJECT_NAME}Targets
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin)
install(TARGETS cjpeg djpeg jpegtran
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin)
if(NOT CMAKE_VERSION VERSION_LESS "3.1" AND MSVC_LIKE AND
  CMAKE_C_LINKER_SUPPORTS_PDB)
  install(FILES "$<TARGET_PDB_FILE:jpeg>"
    DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin OPTIONAL)
endif()
