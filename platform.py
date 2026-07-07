from platformio.platform.base import PlatformBase


class NeuroBoardPlatform(PlatformBase):
    def configure_default_packages(self, variables, targets):
        self.packages = self.packages.copy()
        return super().configure_default_packages(variables, targets)

    def get_build_script(self):
        return self.get_package_dir(
            "framework-arduinoespressif32"
        ) + "/tools/platformio-build.py"
