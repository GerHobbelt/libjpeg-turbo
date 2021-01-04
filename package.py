# -*- coding: utf-8 -*-

name = 'libjpeg_turbo'

version = '2.0.5-ta.1.1.0'

authors = [
    'benjamin.skinner',
]

requires = [
]

@early()
def private_build_requires():
    import sys
    if 'win' in str(sys.platform):
        return ['visual_studio']
    else:
        return ['gcc-6']

variants = [
    ['platform-windows', 'arch-x64', 'os-windows-10'],
    ['platform-linux', 'arch-x86_64', 'os-centos-7'],
]

def commands():

    # Split and store version and package version
    split_versions = str(version).split('-')
    env.LIBJPEG_TURBO_VERSION.set(split_versions[0])
    env.LIBJPEG_TURBO_PACKAGE_VERSION.set(split_versions[1])

    env.LIBJPEG_TURBO_ROOT.set("{root}")
    env.LIBJPEG_TURBO_INCLUDE_DIR.set("{root}/include")
    env.LIBJPEG_TURBO_LIBRARY_DIR.set("{root}/lib")
    env.LIBJPEG_TURBO_BINARY_DIR.set("{root}/bin")

    env.PATH.append( str(env.LIBJPEG_TURBO_BINARY_DIR) )
