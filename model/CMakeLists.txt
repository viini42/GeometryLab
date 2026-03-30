set(TARGET_NAME Model)

add_library(${TARGET_NAME} canvas.cpp scene.cpp
    entities/pointer_ent.cpp
    entities/pointer_ent.hpp
    entities/polyline_ent.cpp
    entities/polyline_ent.hpp
    color.hpp
    world_limits.cpp
    world_limits.hpp)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE Geometry CompilerOptions)