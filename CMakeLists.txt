cmake_minimum_required(VERSION 3.20)
project(sort_utils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(sort_utils INTERFACE)
add_library(sort_utils::sort_utils ALIAS sort_utils)

target_include_directories(sort_utils INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(sort_utils INTERFACE /W4 /permissive-)
else()
  target_compile_options(sort_utils INTERFACE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
enable_testing()

add_executable(sort_utils_basic_test tests/test_basic.cpp)
target_link_libraries(sort_utils_basic_test PRIVATE sort_utils::sort_utils)
add_test(NAME sort_utils.basic COMMAND sort_utils_basic_test)
