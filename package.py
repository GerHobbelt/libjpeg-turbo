name = "libjpeg_turbo"

authors = ["Libjpeg"]

version = "2.1.0"

description = \
    """
    JPEG image codec that uses SIMD instructions (MMX, SSE2, AVX2, Neon, AltiVec)
    to accelerate baseline JPEG compression and decompression.
    """

with scope("config") as c:
    # Determine location to release: internal (int) vs external (ext)

    # NOTE: Modify this variable to reflect the current package situation
    release_as = "ext"

    # The `c` variable here is actually rezconfig.py
    # `release_packages_path` is a variable defined inside rezconfig.py

    import os
    if release_as == "int":
        c.release_packages_path = os.environ["SSE_REZ_REPO_RELEASE_INT"]
    elif release_as == "ext":
        c.release_packages_path = os.environ["SSE_REZ_REPO_RELEASE_EXT"]

requires = [

]

private_build_requires = [
    "cmake",
    "gcc",
]

variants = [
    ["platform-linux", "arch-x86_64", "os-centos-7"]
]

tools = [
]

uuid = "repository.libjpeg-turbo"

def commands():
    env.LIBJPEG_TURBO_ROOT = "{root}"
    env.LIBJPEG_TURBO_LOCATION = "{root}"
    env.JPEG_TURBO_ROOT = "{root}"
    env.JPEG_TURBO_LOCATION = "{root}"
    env.JPEG_ROOT = "{root}"
    env.JPEG_LOCATION = "{root}"
    env.PATH.append("{root}/bin")
