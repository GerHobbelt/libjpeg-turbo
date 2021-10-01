from conans import ConanFile


class JpegConan(ConanFile):
    name = "jpeg"
    version = "2.0.6"
    url = "https://github.com/Esri/libjpeg-turbo/tree/runtimecore"
    license = "https://github.com/Esri/libjpeg-turbo/blob/runtimecore/LICENSE.md"
    description = "libjpeg-turbo is a JPEG image codec that uses SIMD instructions to accelerate JPEG compression and decompression."

    # RTC specific triple
    settings = "platform_architecture_target"

    def package(self):
        base = self.source_folder + "/"
        relative = "3rdparty/libjpeg-turbo/"

        # headers
        self.copy("jconfig.h", src=base, dst=relative)
        self.copy("jerror.h", src=base, dst=relative)
        self.copy("jmorecfg.h", src=base, dst=relative)
        self.copy("jpeglib.h", src=base, dst=relative)

        # libraries
        output = "output/" + str(self.settings.platform_architecture_target) + "/staticlib"
        self.copy("*" + self.name + "*", src=base + "../../" + output, dst=output)
