from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class requestRecipe(ConanFile):
    name = "request"
    version = "0.0.1"
    package_type = "application"

    license = "MIT"
    author = "Saman-Safaei-Dev"
    description = "Simple request maker application."

    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("libcurl/8.9.1")
        self.requires("wxwidgets/3.2.5")

    def layout(self):
        cmake_layout(self)

    def configure(self):
        self.options["libcurl"].with_c_ares = True

        if self.settings.os == "Linux":
            self.options["libcurl"].shared = True
        
        if self.settings.os == "Windows":
            self.options["libcurl"].with_ssl = "schannel"

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
