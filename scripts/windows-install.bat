git submodule update --init --recursive

.\vcpkg\bootstrap-vcpkg.bat -disableMetrics 

.\vcpkg\vcpkg.exe install --triplet x64-windows