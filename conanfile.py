from conan import ConanFile


class TaskQueueRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    options = {"testing": [True, False]}
    default_options = {"testing": False, "soci/*:with_sqlite3": True}

    def requirements(self):
        self.requires("sqlite3/3.44.2")
        self.requires("soci/4.0.3")
        self.requires("grpc/1.54.3")
        if self.options.testing:
            self.requires("catch2/3.5.2")

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")
