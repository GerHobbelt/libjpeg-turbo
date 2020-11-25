# -*- coding: utf-8 -*-

name = "libjpeg-turbo"

version = "2.0.90"

authors = [
    "LibJPEG"
]

requires = [
    "gcc",
    "cmake",
]

def commands():
    env.LIBJPEG_TURBO_ROOT = "{root}"
    env.LIBJPEG_TURBO_LOCATION = "{root}"
    env.JPEG_TURBO_ROOT = "{root}"
    env.JPEG_TURBO_LOCATION = "{root}"
    env.JPEG_ROOT = "{root}"
    env.JPEG_LOCATION = "{root}"
    env.PATH.append("{root}/bin")

uuid = "repository.libjpeg-turbo"
