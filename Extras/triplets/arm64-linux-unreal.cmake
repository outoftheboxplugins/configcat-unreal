set(VCPKG_TARGET_ARCHITECTURE arm64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

set(VCPKG_CMAKE_SYSTEM_NAME Linux)

set(VCPKG_CXX_FLAGS_RELEASE "-stdlib=libc++ -mno-outline-atomics -std=c++98")
set(VCPKG_C_FLAGS_RELEASE "-stdlib=libc++ -mno-outline-atomics -std=c++98")
set(VCPKG_LINKER_FLAGS_RELEASE "-stdlib=libc++ -mno-outline-atomics -std=c++98")
