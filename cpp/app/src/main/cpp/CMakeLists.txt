cmake_minimum_required(VERSION 3.10.2)
project("usemediafilter")
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-DCORE_PLUGIN_VERSION="6.0.0.302")
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/so/${ANDROID_ABI})
find_library(log-lib log)

add_library(native-lib SHARED native-lib.cpp)
target_include_directories(native-lib PRIVATE include)
target_link_libraries(native-lib ${log-lib} avpbase mediafilter corebase hawrap)