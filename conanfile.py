from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout

class GoBlock(ConanFile):
    name = "goblock"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    description = "GoBlock Destroyer Game"

    def requirements(self):
        self.requires("raylib/4.0.0")
        self.requires("flecs/3.2.8")
        # self.requires("entt/3.12.2")

    def build_requirements(self):
        self.tool_requires("cmake/3.26.4")
        
    # def layout(self):
        # cmake_layout(self)
