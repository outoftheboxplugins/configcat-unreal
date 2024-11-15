set(VCPKG_TARGET_ARCHITECTURE arm64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

set(VCPKG_CMAKE_CONFIGURE_OPTIONS "-DCMAKE_CXX_EXTENSIONS=OFF")

set(VCPKG_CXX_FLAGS_RELEASE "-stdlib=libc++ -mno-outline-atomics")
set(VCPKG_C_FLAGS_RELEASE "-stdlib=libc++ -mno-outline-atomics")
set(VCPKG_LINKER_FLAGS_RELEASE "-stdlib=libc++ -mno-outline-atomics")
