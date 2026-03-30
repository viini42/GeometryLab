set(TARGET_NAME Renderer)

add_library(${TARGET_NAME} window.cpp
    camera.cpp
    camera.hpp
    renderer.cpp
    renderer.hpp)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE Model Geometry CompilerOptions)

find_package(SFML REQUIRED COMPONENTS Graphics Window)
target_link_libraries(${TARGET_NAME} PUBLIC SFML::Graphics SFML::Window)
