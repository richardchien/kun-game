cmake_minimum_required(VERSION 3.9)
project(kun)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "/MP ${CMAKE_CXX_FLAGS}")  # build with object level parallelism

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include(FindVcpkgIncludeDir)

include_directories(${VCPKG_INCLUDE_DIR})
include_directories(src)

set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:LIBCMT")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:LIBCMTD")

add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                -D_SCL_SECURE_NO_WARNINGS
                -D_WIN32_WINNT=0x0501
                -DWIN32_LEAN_AND_MEAN)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.c)
add_executable(kun ${SOURCE_FILES})
