cmake_minimum_required(VERSION 3.24)

# Configure vcpkg toolchain
if(NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
    set(VCPKG_TARGET_TRIPLET x64-windows-static)
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
    set(VCPKG_TARGET_TRIPLET x64-linux)
  else()
    message(FATAL_ERROR "Unsupported platform")
  endif()

  # set(VCPKG_INSTALL_OPTIONS "--no-print-usage")

  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif()

project(Drawer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(ProjectSetup INTERFACE)

message(STATUS "Setting up platform = ${CMAKE_SYSTEM_NAME}")
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_compile_definitions(ProjectSetup INTERFACE PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_compile_definitions(ProjectSetup INTERFACE PLATFORM_LINUX)
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

message(STATUS "Setting up compiler flags = ${CMAKE_CXX_COMPILER_ID}:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}")
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(ProjectSetup INTERFACE
      /Wall                        # Enable most common warnings
      /W4                          # Set warning level 4 (highest warning level)
      $<$<CONFIG:Release>:/WX>     # Treat warnings as errors
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(ProjectSetup INTERFACE
      -Wall                        # Enable most common warnings
      -Wextra                      # Enable extra warnings
      -Wpedantic                   # Issue all the warnings demanded by strict ISO C and ISO C++
      $<$<CONFIG:Release>:-Werror> # Treat warnings as errors
      -Wconversion                 # Warn for implicit conversions that may change the value
      -Wsign-conversion            # Warn for signed-to-unsigned conversion
      -Wunreachable-code           # Warn if the compiler detects code that will never be executed
      -Wunused                     # Warn about variables or functions that are defined but never used
      -Wunused-parameter           # Warn about unused function parameters
      -Wunused-variable            # Warn about unused variables
      -Wfloat-equal                # Warn if floating-point values are compared for equality
      -Wshadow                     # Warn whenever a local variable shadows another local variable
      -Wuninitialized              # Warn about uninitialized variables
      -Wmaybe-uninitialized        # Warn about variables that may be uninitialized
      -Wunused-label               # Warn when a label is declared but not used
      -Wsuggest-override           # Warn if a function could be marked override
      -Wnon-virtual-dtor           # Warn when a class has a non-virtual destructor
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC" OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
    target_compile_options(ProjectSetup INTERFACE
        -Wall                        # Enable most warning messages
        -Wextra                      # Enable some extra warning messages
        -Wpedantic                   # Warn about non-portable constructs
        $<$<CONFIG:Release>:-Werror> # Treat warnings as errors
        -Wshadow                     # Warn whenever a local variable shadows another local variable
        -Wconversion                 # Warn for implicit conversions that may change the value
        -Wsign-conversion            # Warn for implicit conversions that may change the sign
        -Wformat=2                   # Check printf/scanf format strings
        -Wundef                      # Warn if an undefined identifier is evaluated in an #if directive
        -Wunreachable-code           # Warn if code will never be executed
        -Wunused                     # Warn about unused functions, variables, etc.
    )
  else()
    message(FATAL_ERROR "Unsupported CLANG frontend (CMAKE_CXX_COMPILER_FRONTEND_VARIANT = ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT})")
  endif()
else()
  message(FATAL_ERROR "Unsupported compiler (CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID})")
endif()

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_library(DrawerLib STATIC world_converter.hpp world_converter.cpp
    point.cpp
    point.hpp
    line.cpp
    line.hpp
    object_drawer.cpp
    object_drawer.hpp)
target_link_libraries(DrawerLib PUBLIC sfml-system sfml-network sfml-graphics sfml-window)

add_executable(Drawer main.cpp)
target_link_libraries(Drawer PRIVATE ProjectSetup DrawerLib)

enable_testing()

find_package(GTest CONFIG REQUIRED)
add_executable(DrawerTests tests.cpp)
target_link_libraries(DrawerTests PRIVATE DrawerLib GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

#add_test(AllTestsInMain main)