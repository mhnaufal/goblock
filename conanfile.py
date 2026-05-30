from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout

class GoBlock(ConanFile):
    name = "goblock"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    # generators = "CMakeToolchain", "CMakeDeps"
    description = "GoBlock Destroyer Game"
    user = "mhnaufal"

    def requirements(self):
        self.requires("raylib/6.0")
        self.requires("flecs/4.1.5")
        # self.requires("entt/3.12.2")

    def build_requirements(self):
        self.tool_requires("cmake/3.26.4")
        
    def layout(self):
        self.folders.build = "build"
        self.folders.generators = "generators"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()
