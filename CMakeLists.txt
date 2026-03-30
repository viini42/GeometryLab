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

project(GeometryLab CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CompilerOptions.cmake)
add_subdirectory(app)
add_subdirectory(geometry)
add_subdirectory(model)
add_subdirectory(renderer)
#
#
#find_package(SFML REQUIRED COMPONENTS Graphics Window)
#
#add_library(DrawerLib STATIC
#    domain/geometry/line.cpp
#    domain/geometry/line.hpp
#    domain/geometry/point.cpp
#    domain/geometry/point.hpp
#    domain/geometry/world_converter.cpp
#    domain/geometry/world_converter.hpp
#    domain/model.cpp
#    domain/model.hpp
#    draw/object_drawer.cpp
#    draw/object_drawer.hpp
#    draw/canvas.cpp
#    draw/canvas.hpp
#    io/model_loader.cpp
#    io/model_loader.hpp
#    draw/window.cpp
#    draw/window.hpp
#)
#target_include_directories(DrawerLib PUBLIC ${CMAKE_SOURCE_DIR})
#target_link_libraries(DrawerLib PUBLIC SFML::Graphics SFML::Window)
#if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#  set_target_properties(DrawerLib PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#endif()
#
#add_executable(Drawer main.cpp
#    controllers/canvas_handler.cpp
#    controllers/canvas_handler.hpp
#    app/application.cpp
#    app/application.hpp)
#target_link_libraries(Drawer PRIVATE ProjectSetup DrawerLib)
#if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#  target_compile_definitions(Drawer PRIVATE SFML_STATIC)
#  set_target_properties(Drawer PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#endif()
#enable_testing()
#
#find_package(GTest CONFIG REQUIRED)
#add_executable(DrawerTests tests/tests.cpp)
#target_link_libraries(DrawerTests PRIVATE DrawerLib GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
#if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#  set_target_properties(DrawerTests PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#endif()
